//
// Created by mac on 08.01.2021.
//

#include "server.h"

t_message_info *messages;
int count;

static int get_last_messages_callback(void *NotUsed, int argc, char **argv, char **azColName) {
    t_message_info *m = (t_message_info*)malloc(sizeof(t_message_info));
    m->next = messages;
    messages = m;
    count++;
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
    count = 0;
    char sql[1024];
    snprintf(sql, sizeof(sql),
             "SELECT Id, User, Text, Time FROM Messages WHERE Chat = '%d';",chat);
    rc = sqlite3_exec(db, sql, get_last_messages_callback, 0, &err_msg);
    if (rc != SQLITE_OK ) {
        fprintf(stderr, "Failed to select data\n");
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
    }

    t_message *mes = (t_message*)malloc(sizeof(t_message));
    mes->count = count;
    mes->id = (int*)malloc(count * sizeof(int));
    mes->user = (int*)malloc(count * sizeof(int));
    mes->text = (char**)malloc(count * sizeof(char*));
    for (int i = count-1; i >= 0; i--) {
        mes->id[i] = messages->id;
        mes->user[i] = messages->user;
        mes->text[i] = messages->text;
        t_message_info *tmp = messages;
        messages = messages->next;
        free(tmp);
    }
    return mes;
}
