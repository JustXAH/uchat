#include "server.h"

char *gf_filename;

static int get_filename_callback(void *NotUsed, int argc, char **argv, char **azColName) {
    if (argc)
        gf_filename = mx_strdup(argv[0]);
    return 0;
}

char* mx_db_get_filename(sqlite3 *db, int id) {
    char *err_msg = 0;
    int rc;
    char sql[1024];
    gf_filename = 0;

    snprintf(sql, sizeof(sql),
             "SELECT Filename FROM Files WHERE Id = '%d';",id);
    rc = sqlite3_exec(db, sql, get_filename_callback, 0, &err_msg);
    if (rc != SQLITE_OK ) {
        fprintf(stderr, "Failed to select data\n");
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
    }
    return gf_filename;
}
