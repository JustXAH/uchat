#include "server.h"

typedef struct s_id_node {
    int id;
    struct s_id_node *next;
}              t_id_node;

t_id_node *subs_id_list;
int subs_count;

static int search_users_callback(void *NotUsed, int argc, char **argv, char **azColName) {
    subs_count++;
    t_id_node *id = (t_id_node*)malloc(sizeof(t_id_node));
    id->id = mx_atoi(argv[0]);
    id->next = subs_id_list;
    subs_id_list = id;
    return 0;
}

int *mx_db_search_users_by_substr(sqlite3 *db, char *str) {
    char *err_msg = 0;
    int rc;

    char sql[1024];
    subs_count = 0;
    snprintf(sql, sizeof(sql),
             "SELECT Id FROM Users WHERE Login LIKE '%%%s%%';",str);
    rc = sqlite3_exec(db, sql, search_users_callback, 0, &err_msg);
    if (rc != SQLITE_OK ) {
        fprintf(stderr, "Failed to select data\n");
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
    }

    if (!subs_id_list)
        return NULL;

    int *users = (int *)malloc((subs_count+1) * sizeof(int));
    users[subs_count--] = 0;
    while (subs_id_list) {
        t_id_node *tmp = subs_id_list;
        users[subs_count--] = subs_id_list->id;
        subs_id_list = subs_id_list->next;
        free(tmp);
    }
    return users;
}
