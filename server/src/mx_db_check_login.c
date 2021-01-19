//
// Created by mac on 08.01.2021.
//

#include "server.h"

t_user *users;

static int check_login_callback(void *NotUsed, int argc, char **argv, char **azColName) {
    t_user *u = (t_user*)malloc(sizeof(t_user));
    u->next = NULL;
    if (!users)
        users = u;
    else {
        t_user *cur_u = users;
        while (cur_u->next)
            cur_u = cur_u->next;
        cur_u->next = u;
    }
    NotUsed = 0;
    for (int i = 0; i < argc; i++) {
        if (!mx_strcmp(azColName[i],"Id"))
            u->id = argv[i] ? mx_atoi(argv[i]) : 0;
        if (!mx_strcmp(azColName[i],"Login"))
            u->login = mx_strdup(argv[i]);
        if (!mx_strcmp(azColName[i],"Password"))
            u->password = mx_strdup(argv[i]);

        //printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    return 0;
}

int mx_db_check_login(sqlite3 *db, char *login, char *password) {
    char *err_msg = 0;
    int rc;
    users = NULL;
    char sql[1024];
    snprintf(sql, sizeof(sql),
             "SELECT Id, Login, Password FROM Users WHERE Login = '%s';",login);
    rc = sqlite3_exec(db, sql, check_login_callback, 0, &err_msg);
    if (rc != SQLITE_OK ) {
        fprintf(stderr, "Failed to select data\n");
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
    }
    if (!users)
        return 0;
    int res_id = -1;
    if (!mx_strcmp(users->password, password))
        res_id = users->id;
    t_user *tmp;
    while (users != NULL) {
        tmp = users;
        users = users->next;
        free(tmp->login);
        free(tmp->password);
        free(tmp);
    }
    return res_id;
}
