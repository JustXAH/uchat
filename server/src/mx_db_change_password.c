#include "server.h"

int mx_db_change_password(sqlite3* db, int user, char* new_password){
    char *err_msg = 0;
    int rc;
    char sql[1024];
    snprintf(sql, sizeof(sql),
          "UPDATE Users SET Password = '%s' WHERE Id = '%d';",new_password,user);
    rc = sqlite3_exec(db, sql, 0, 0, &err_msg);
    if (rc != SQLITE_OK ) {
        fprintf(stderr, "Failed to change password\n");
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
        return 1;
    }
    return 0;
}
