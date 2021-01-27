#include "server.h"

int mx_db_insert_new_file(sqlite3 *db, char *filename) {
    char *err_msg = 0;
    int rc;

    char sql[1024];
    snprintf(sql, sizeof(sql),
             "INSERT INTO Files(Filename) VALUES ('%s');",filename);

    rc = sqlite3_exec(db, sql, 0, 0, &err_msg);

    if (rc != SQLITE_OK ) {
        fprintf(stderr, "Failed to insert user\n");
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
    } else {
        fprintf(stdout, "New file created successfully\n");
    }
    int last_id = sqlite3_last_insert_rowid(db);
    snprintf(sql, sizeof(sql),
             "UPDATE Files SET Filename = '%d_%s' WHERE Id = '%d';",last_id,filename,last_id);

    rc = sqlite3_exec(db, sql, 0, 0, &err_msg);


    return last_id;
}
