#include "server.h"

int mx_db_clear_notification(sqlite3 *db, int chat_id, int user_id) {
    char *err_msg = 0;
    int rc;

    char sql[1024];
    snprintf(sql, sizeof(sql),
             "UPDATE Chats SET Notification = 0 WHERE Id = '%d' AND user = '%d'",chat_id,user_id);
    rc = sqlite3_exec(db, sql, 0, 0, &err_msg);
    if (rc != SQLITE_OK ) {
        fprintf(stderr, "Failed to clear notification\n");
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
        return 1;
    }
    snprintf(sql, sizeof(sql),
             "UPDATE Chats SET Notification2 = 0 WHERE Id = '%d' AND User2 = '%d'",chat_id,user_id);
    rc = sqlite3_exec(db, sql, 0, 0, &err_msg);
    if (rc != SQLITE_OK ) {
        fprintf(stderr, "Failed to clear notification\n");
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
        return 1;
    }

    return 0;
}
