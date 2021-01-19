#include "server.h"

char *login;

static int get_login_callback(void *NotUsed, int argc, char **argv, char **azColName) {
    if (argc)
        login = mx_strdup(argv[0]);
    return 0;
}

char* mx_db_get_login(sqlite3 *db, int user) {
    char *err_msg = 0;
    int rc;
    login = 0;

    char sql[1024];
    snprintf(sql, sizeof(sql),
             "SELECT Login FROM Users WHERE Id = '%d';",user);
    rc = sqlite3_exec(db, sql, get_login_callback, 0, &err_msg);
    if (rc != SQLITE_OK ) {
        fprintf(stderr, "Failed to select data\n");
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
    }
    return login;
}
