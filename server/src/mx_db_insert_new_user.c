//
// Created by Igor Khanenko on 08.01.2021.
//

#include "server.h"

int mx_db_insert_new_user(sqlite3 *db, char *login, char *password) {
    char *err_msg = 0;
    int rc;

    char sql[1024];
    snprintf(sql, sizeof(sql),
             "INSERT INTO Users(Login,Password) VALUES ('%s','%s');",login,password);

    rc = sqlite3_exec(db, sql, 0, 0, &err_msg);

    if (rc != SQLITE_OK ) {
        fprintf(stderr, "Failed to create table\n");
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
    } else {
        fprintf(stdout, "Table Users created successfully\n");
    }

    int last_id = sqlite3_last_insert_rowid(db);
    printf("The last Id of the inserted row is %d\n", last_id);
    return last_id;
}
