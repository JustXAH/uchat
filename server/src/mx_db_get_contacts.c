#include "server.h"

typedef struct s_id_node {
    int id;
    struct s_id_node *next;
}              t_id_node;

extern t_id_node *id_list;
extern int count;

static int get_contacts_callback(void *NotUsed, int argc, char **argv, char **azColName) {
    count++;
    t_id_node *id = (t_id_node*)malloc(sizeof(t_id_node));
    id->id = mx_atoi(argv[0]);
    id->next = id_list;
    id_list = id;
    return 0;
}

int *mx_db_get_contacts(sqlite3 *db, int user) {
    char *err_msg = 0;
    int rc;

    char sql[1024];
    count = 0;
    snprintf(sql, sizeof(sql),
             "SELECT Contact FROM Contacts WHERE User = '%d';",user);
    rc = sqlite3_exec(db, sql, get_contacts_callback, 0, &err_msg);
    if (rc != SQLITE_OK ) {
        fprintf(stderr, "Failed to select data\n");
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
    }

    if (!id_list)
        return NULL;

    int *contacts = (int *)malloc((count+1) * sizeof(int));
    contacts[count--] = 0;
    while (id_list) {
        t_id_node *tmp = id_list;
        contacts[count--] = id_list->id;
        id_list = id_list->next;
        free(tmp);
    }
    return contacts;
}
