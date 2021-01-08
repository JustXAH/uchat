#include "server.h"

typedef struct s_id_node {
    int id;
    struct s_id_node *next;
}              t_id_node;

t_id_node *id_list;
int count;

static int get_contacts_callback(void *NotUsed, int argc, char **argv, char **azColName) {
    count++;
    t_id_node *id = (t_id_node*)malloc(sizeof(t_id_node));
    id->id = mx_atoi(argv[0]);
    id->next = id_list;
    id_list = id;
    return 0;
}

int *mx_db_search_users_by_substr(sqlite3 *db, char *str) {
    char *err_msg = 0;
    int rc;

    char sql[1024];
    count = 0;
    snprintf(sql, sizeof(sql),
             "SELECT Id FROM Users WHERE Login LIKE '%%%s%%';",str);
    rc = sqlite3_exec(db, sql, get_contacts_callback, 0, &err_msg);
    if (rc != SQLITE_OK ) {
        fprintf(stderr, "Failed to select data\n");
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
    }

    if (!id_list)
        return NULL;

    int *users = (int *)malloc((count+1) * sizeof(int));
    users[count--] = 0;
    while (id_list) {
        t_id_node *tmp = id_list;
        users[count--] = id_list->id;
        id_list = id_list->next;
        free(tmp);
    }
    return users;
}
