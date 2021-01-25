#include "server.h"

typedef struct s_id_node {
    int id;
    struct s_id_node *next;
}              t_id_node;

t_id_node *gc_id_list;
int gc_count;

static int mx_get_chats_callback(void *NotUsed, int argc, char **argv, char **azColName) {
    gc_count++;
    t_id_node *id = (t_id_node*)malloc(sizeof(t_id_node));
    id->id = mx_atoi(argv[0]);
    id->next = gc_id_list
;
    gc_id_list
 = id;
    return 0;
}

int *mx_db_get_chats(sqlite3 *db, int user) {
    char *err_msg = 0;
    int rc;
    gc_count = 0;
    char sql[1024];
    snprintf(sql, sizeof(sql),
             "SELECT Id FROM Chats WHERE (User = '%d' OR User2 = '%d');",user,user);

    rc = sqlite3_exec(db, sql, mx_get_chats_callback, 0, &err_msg);

    if (rc != SQLITE_OK ) {
        fprintf(stderr, "Failed to select data\n");
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
    }
    int *chats = (int *)malloc((gc_count+1) * sizeof(int));
    chats[gc_count--] = 0;
    while (gc_id_list
) {
        t_id_node *tmp = gc_id_list
    ;
        chats[gc_count--] = gc_id_list
    ->id;
        gc_id_list
     = gc_id_list
    ->next;
        free(tmp);
    }
    return chats;
}
