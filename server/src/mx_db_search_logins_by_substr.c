#include "server.h"

typedef struct s_login_node {
    char *login;
    struct s_login_node *next;
}              t_login_node;

t_login_node *login_list;
int slbs_count;

static int search_logins_callback(void *NotUsed, int argc, char **argv, char **azColName) {
    slbs_count++;
    t_login_node *lgn = (t_login_node*)malloc(sizeof(t_login_node));
    lgn->login = mx_strdup(argv[0]);
    lgn->next = login_list;
    login_list = lgn;
    return 0;
}

char** mx_db_search_logins_by_substr(sqlite3 *db, char *str) {
    char *err_msg = 0;
    int rc;

    char sql[1024];
    slbs_count = 0;
    snprintf(sql, sizeof(sql),
             "SELECT Login FROM Users WHERE Login LIKE '%%%s%%';",str);
    rc = sqlite3_exec(db, sql, search_logins_callback, 0, &err_msg);
    if (rc != SQLITE_OK ) {
        fprintf(stderr, "Failed to select data\n");
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
    }

    if (!login_list)
        return NULL;

    char **logins = (char**)malloc((slbs_count+1) * sizeof(char*));
    logins[slbs_count--] = NULL;
    while (login_list) {
        t_login_node *tmp = login_list;
        logins[slbs_count--] = login_list->login;
        login_list = login_list->next;
        free(tmp);
    }
    return logins;
}
