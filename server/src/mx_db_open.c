//
// Created by Igor Khanenko on 08.01.2021.
//

#include "server.h"

sqlite3* mx_db_open(char *filename) {
    sqlite3 *db;
    sqlite3_stmt *res;

    int rc = sqlite3_open(filename, &db);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return NULL;
    }

    rc = sqlite3_prepare_v2(db, "SELECT SQLITE_VERSION()", -1, &res, 0);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to fetch data: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return NULL;
    }

    rc = sqlite3_step(res);
    if (rc == SQLITE_ROW) {
        printf("ver = %s\n", sqlite3_column_text(res, 0));
    }

    sqlite3_finalize(res);
    return db;
}
