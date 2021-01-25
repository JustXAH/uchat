//
// Created by mac on 08.01.2021.
//

#include "server.h"

int le_login_id;

static int check_login_exist_callback(void *NotUsed, int argc, char **argv, char **azColName) {
    if (argc)
        le_login_id = mx_atoi(argv[0]);
    return 0;
}

int mx_db_check_login_exist(sqlite3 *db, char *login) {
    char *err_msg = 0;
    int rc;
    char sql[1024];
    le_login_id = 0;
    snprintf(sql, sizeof(sql),
             "SELECT Id FROM Users WHERE Login = '%s';",login);

    rc = sqlite3_exec(db, sql, check_login_exist_callback, 0, &err_msg);

    if (rc != SQLITE_OK ) {
        fprintf(stderr, "Failed to select data\n");
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
    }

    return le_login_id;
}
