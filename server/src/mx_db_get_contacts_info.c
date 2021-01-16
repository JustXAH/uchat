#include "server.h"

typedef struct s_user_node {
    int id;
    char *login;
    struct s_user_node *next;
}              t_user_node;

t_user_node *user_info;
int count;

static int get_contacts_info_callback(void *NotUsed, int argc, char **argv, char **azColName) {
    t_user_node *u = (t_user_node*)malloc(sizeof(t_user_node));
    u->next = user_info;
    user_info = u;
    count++;
    NotUsed = 0;
    for (int i = 0; i < argc; i++) {
        if (!mx_strcmp(azColName[i],"Contact"))
            u->id = argv[i] ? mx_atoi(argv[i]) : 0;
        if (!mx_strcmp(azColName[i],"Login"))
            u->login = mx_strdup(argv[i]);
    }
    return 0;
}

t_contact *mx_db_get_contacts_info(sqlite3 *db, int user) {
    char *err_msg = 0;
    int rc;
    user_info = NULL;
    count = 0;
    char sql[1024];
    snprintf(sql, sizeof(sql),
             "SELECT Contact, Login FROM Contacts JOIN Users ON Contacts.Contact = Users.Id WHERE User = '%d';",user);
    rc = sqlite3_exec(db, sql, get_contacts_info_callback, 0, &err_msg);
    if (rc != SQLITE_OK ) {
        fprintf(stderr, "Failed to select data\n");
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
    }
    t_contact *contacts = (t_contact*)malloc(sizeof(t_contact));
    contacts->count = count;
    contacts->id = (int*)malloc(count * sizeof(int));
    contacts->login = (char**)malloc(count * sizeof(char*));
    for (int i = count-1; i >= 0; i--) {
        contacts->id[i] = user_info->id;
        contacts->login[i] = user_info->login;
        t_user_node *tmp = user_info;
        user_info = user_info->next;
        free(tmp);
    }
    return contacts;
}
