//
// Created by Igor Khanenko on 08.01.2021.
//

#include "server.h"

int mx_db_insert_new_user(sqlite3 *db, char *login, char *password) {
    char *err_msg = 0;
    int rc;

    if (mx_db_check_login_exist(db,login))
        return 0;

    char sql[1024];
    snprintf(sql, sizeof(sql),
             "INSERT INTO Users(Login,Password,Picture) VALUES ('%s','%s', '0');",login,password);

    rc = sqlite3_exec(db, sql, 0, 0, &err_msg);

    if (rc != SQLITE_OK ) {
        fprintf(stderr, "Failed to insert user\n");
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
    } else {
        fprintf(stdout, "New user created successfully\n");
    }

    int last_id = sqlite3_last_insert_rowid(db);
    return last_id;
}
