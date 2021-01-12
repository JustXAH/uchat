#include "server.h"

t_user_info *user_info;

static int get_contacts_info_callback(void *NotUsed, int argc, char **argv, char **azColName) {
    t_user_info *u = (t_user_info*)malloc(sizeof(t_user_info));
    u->next = user_info;
    user_info = u;

    NotUsed = 0;
    for (int i = 0; i < argc; i++) {
        if (!mx_strcmp(azColName[i],"Contact"))
            u->id = argv[i] ? mx_atoi(argv[i]) : 0;
        if (!mx_strcmp(azColName[i],"Login"))
            u->login = mx_strdup(argv[i]);
    }
    return 0;
}

t_user_info *mx_db_get_contacts_info(sqlite3 *db, int user) {
    char *err_msg = 0;
    int rc;
    user_info = NULL;
    char sql[1024];
    snprintf(sql, sizeof(sql),
             "SELECT Contact, Login FROM Contacts JOIN Users ON Contacts.Contact = Users.Id WHERE User = '%d';",user);
    rc = sqlite3_exec(db, sql, get_contacts_info_callback, 0, &err_msg);
    if (rc != SQLITE_OK ) {
        fprintf(stderr, "Failed to select data\n");
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
    }

    return user_info;
}
