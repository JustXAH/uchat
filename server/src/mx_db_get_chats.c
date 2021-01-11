#include "server.h"

typedef struct s_id_node {
    int id;
    struct s_id_node *next;
}              t_id_node;

t_id_node *id_list;
int count;

static int mx_get_chats_callback(void *NotUsed, int argc, char **argv, char **azColName) {
    count++;
    t_id_node *id = (t_id_node*)malloc(sizeof(t_id_node));
    id->id = mx_atoi(argv[0]);
    id->next = id_list;
    id_list = id;
    return 0;
}

int *mx_db_get_chats(sqlite3 *db, int user) {
    char *err_msg = 0;
    int rc;
    count = 0;
    char sql[1024];
    snprintf(sql, sizeof(sql),
             "SELECT Id FROM Chats WHERE (User = '%d' OR User2 = '%d');",user,user);

    rc = sqlite3_exec(db, sql, mx_get_chats_callback, 0, &err_msg);

    if (rc != SQLITE_OK ) {
        fprintf(stderr, "Failed to select data\n");
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
    }
    int *chats = (int *)malloc((count+1) * sizeof(int));
    chats[count--] = 0;
    while (id_list) {
        t_id_node *tmp = id_list;
        chats[count--] = id_list->id;
        id_list = id_list->next;
        free(tmp);
    }
    return chats;
}
