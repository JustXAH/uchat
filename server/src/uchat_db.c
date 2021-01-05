#include <stdio.h>
#include <uchat_db.h>

sqlite3* db_open(char *filename) {
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


int db_close(sqlite3 *db){
    sqlite3_close(db);
    return 0;
}

// int db_init(sqlite3 *db) {
// "CREATE TABLE Users(Id INTEGER PRIMARY KEY, Login TEXT, Password TEXT);"
// }

int db_insert_new_user(sqlite3 *db, char *login, char *password) {
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

int db_check_login(sqlite3 *db, char *login, char *password) {
    // char *err_msg = 0;
    // sqlite3_stmt *res;
    // int rc;
    //
    // char *sql = "SELECT Id, Password FROM Users WHERE Login = ?";
    //
    // // rc = sqlite3_prepare_v2(db, sql, login, &res, 0);
    // // if (rc == SQLITE_OK) {
    // //     sqlite3_bind_text(res, 1, login, -1, nil);
    // // } else {
    // //     fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
    // // }
    //
    // int step = sqlite3_step(res);
    //
    // if (step == SQLITE_ROW) {
    //
    //     printf("%s: ", sqlite3_column_text(res, 0));
    //     printf("%s\n", sqlite3_column_text(res, 1));
    //
    // }
    //
    // sqlite3_finalize(res);
    return 0;
}
