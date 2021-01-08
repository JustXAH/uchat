//
// Created by Igor Khanenko on 08.01.2021.
//

#include "server.h"

int mx_db_close(sqlite3 *db) {
    sqlite3_close(db);
    return 0;
}
