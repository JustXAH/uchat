#include "server.h"

int mx_db_set_user_picture(sqlite3 *db, int user, char *filename){
    char *err_msg = 0;
    int rc;

    //ckeck voice EXISTS

    //

    int file_id = mx_db_insert_new_file(db, filename);

    char sql[1024];
    snprintf(sql, sizeof(sql),
             "UPDATE Users SET Picture = '%d' WHERE Id = '%d';", file_id, user);

    rc = sqlite3_exec(db, sql, 0, 0, &err_msg);

    if (rc != SQLITE_OK ) {
        fprintf(stderr, "Failed to set user photo\n");
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
    } else {
        fprintf(stdout, "Set user photo created successfully\n");
    }

    //int last_id = sqlite3_last_insert_rowid(db);
    return file_id;
}
