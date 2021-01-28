#include "server.h"

int mx_db_delete_contact(sqlite3 *db, int user, int contact) {
    char *err_msg = 0;
    int rc;
    char sql[1024];
    snprintf(sql, sizeof(sql),
             "DELETE FROM Contacts WHERE User = '%d' AND Contact = '%d';",user,contact);

    rc = sqlite3_exec(db, sql, 0, 0, &err_msg);

    if (rc != SQLITE_OK ) {
        fprintf(stderr, "Failed to delete contact\n");
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
        return 1;
    }
    fprintf(stderr, "Delete contact complete\n");
    return 0;
}
