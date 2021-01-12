#include "server.h"

int mx_db_create_new_contact(sqlite3 *db, int user, int contact) {
    char *err_msg = 0;
    int rc;

    char sql[1024];
    snprintf(sql, sizeof(sql),
             "INSERT INTO Contacts(User,Contact) VALUES ('%d','%d');",user,contact);

    rc = sqlite3_exec(db, sql, 0, 0, &err_msg);

    if (rc != SQLITE_OK ) {
        fprintf(stderr, "Failed to insert contact\n");
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
        return -1;
    } else {
        fprintf(stdout, "New contact created successfully\n");
    }

    int last_id = sqlite3_last_insert_rowid(db);
    return last_id;
}
