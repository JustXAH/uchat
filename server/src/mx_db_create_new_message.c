#include "server.h"

int mx_db_create_new_message(sqlite3 *db, int user, int chat, char *text){
    char *err_msg = 0;
    int rc;

    char sql[1024];
    snprintf(sql, sizeof(sql),
             "INSERT INTO Messages(User,Chat,Text,Time) VALUES ('%d','%d','%s','%ld'); \
             UPDATE Chats SET Notification2 = Notification2 + 1 WHERE Id = '%d' AND User = '%d'; \
             UPDATE Chats SET Notification = Notification + 1 WHERE Id = '%d' AND User2 = '%d';"
             ,user,chat,text,time(0),chat,user,chat,user);
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
