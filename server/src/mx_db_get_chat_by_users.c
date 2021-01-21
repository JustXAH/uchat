#include "server.h"

int cby_login_id;

static int mx_get_chat_by_users_callback(void *NotUsed, int argc, char **argv, char **azColName) {
    if (argc)
        cby_login_id = mx_atoi(argv[0]);
    return 0;
}

int mx_db_get_chat_by_users(sqlite3 *db, int user_1, int user_2) {
    char *err_msg = 0;
    int rc;
    cby_login_id = 0;
    char sql[1024];
    snprintf(sql, sizeof(sql),
             "SELECT Id FROM Chats WHERE (User = '%d' AND User2 = '%d') OR (User = '%d' AND User2 = '%d');",user_1,user_2,user_2,user_1);

    rc = sqlite3_exec(db, sql, mx_get_chat_by_users_callback, 0, &err_msg);

    if (rc != SQLITE_OK ) {
        fprintf(stderr, "Failed to select data\n");
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
    }

    return cby_login_id;
}
