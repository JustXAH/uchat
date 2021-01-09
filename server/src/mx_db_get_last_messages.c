//
// Created by mac on 08.01.2021.
//

#include "server.h"

t_message *messages;

static int get_last_messages_callback(void *NotUsed, int argc, char **argv, char **azColName) {
    t_message *m = (t_message*)malloc(sizeof(t_message));
    m->next = messages;
    messages = m;

    NotUsed = 0;
    for (int i = 0; i < argc; i++) {
        if (!mx_strcmp(azColName[i],"Id"))
            m->id = argv[i] ? mx_atoi(argv[i]) : 0;
        if (!mx_strcmp(azColName[i],"User"))
            m->user = argv[i] ? mx_atoi(argv[i]) : 0;
        if (!mx_strcmp(azColName[i],"Text"))
            m->text = mx_strdup(argv[i]);
        if (!mx_strcmp(azColName[i],"Time"))
            m->timestamp = mx_atoi(argv[i]);
    }
    return 0;
}

t_message *mx_db_get_last_messages(sqlite3 *db, int chat) {
    char *err_msg = 0;
    int rc;
    messages = NULL;
    char sql[1024];
    snprintf(sql, sizeof(sql),
             "SELECT Id, User, Text, Time FROM Messages WHERE Chat = '%d';",chat);
    rc = sqlite3_exec(db, sql, get_last_messages_callback, 0, &err_msg);
    if (rc != SQLITE_OK ) {
        fprintf(stderr, "Failed to select data\n");
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
    }

    return messages;
}
