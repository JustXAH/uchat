#include "server.h"

int mx_db_create_new_message(sqlite3 *db, int user, int chat, char *text){
    char *err_msg = 0;
    int rc;

    char sql[1024];
    snprintf(sql, sizeof(sql),
             "INSERT INTO Messages(User,Chat,Text,Time) VALUES ('%d','%d','%s','%ld');",user,chat,text,time(0));

    rc = sqlite3_exec(db, sql, 0, 0, &err_msg);

    if (rc != SQLITE_OK ) {
        fprintf(stderr, "Failed to insert message\n");
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
    } else {
        fprintf(stdout, "New message created successfully\n");
    }

    int last_id = sqlite3_last_insert_rowid(db);
    return last_id;
}
