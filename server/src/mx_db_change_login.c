#include "server.h"

int mx_db_change_login(sqlite3* db, int user, char* new_login) {
     char *err_msg = 0;
     int rc;
     char sql[1024];
     snprintf(sql, sizeof(sql),
              "UPDATE Users SET Login = '%s' WHERE Id = '%d';",new_login,user);
     rc = sqlite3_exec(db, sql, 0, 0, &err_msg);
     if (rc != SQLITE_OK ) {
         fprintf(stderr, "Failed to change login\n");
         fprintf(stderr, "SQL error: %s\n", err_msg);
         sqlite3_free(err_msg);
         return 1;
     }
     return 0;
}
