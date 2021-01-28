#include "server.h"

int mx_db_clear_history(sqlite3 *db, int chat) {
    char *err_msg = 0;
    int rc;
    char sql[1024];
    snprintf(sql, sizeof(sql),
             "DELETE FROM Messages WHERE Chat = '%d';",chat);

    rc = sqlite3_exec(db, sql, 0, 0, &err_msg);

    if (rc != SQLITE_OK ) {
        fprintf(stderr, "Failed to clear chat history\n");
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
        return 1;
    }
    fprintf(stderr, "Clear chat history complete\n");
    return 0;
}
