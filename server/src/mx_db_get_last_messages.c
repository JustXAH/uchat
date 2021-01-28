//
// Created by mac on 08.01.2021.
//

#include "server.h"

t_message_info *glm_messages;
int glm_count;

static int get_last_glm_messages_callback(void *NotUsed, int argc, char **argv, char **azColName) {
    t_message_info *m = (t_message_info*)malloc(sizeof(t_message_info));
    m->next = glm_messages;
    glm_messages = m;
    glm_count++;
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
    glm_messages = NULL;
    glm_count = 0;
    char sql[1024];
    snprintf(sql, sizeof(sql),
             "SELECT Id, User, Text, Time FROM Messages WHERE Chat = '%d';",chat);
    rc = sqlite3_exec(db, sql, get_last_glm_messages_callback, 0, &err_msg);
    if (rc != SQLITE_OK ) {
        fprintf(stderr, "Failed to select data\n");
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
    }

    t_message *mes = (t_message*)malloc(sizeof(t_message));
    mes->count = glm_count;
    mes->id = (int*)malloc(glm_count * sizeof(int));
    mes->user = (int*)malloc(glm_count * sizeof(int));
    mes->text = (char**)malloc(glm_count * sizeof(char*));
    mes->timestamp = (time_t*)malloc(glm_count * sizeof(time_t));
    for (int i = glm_count-1; i >= 0; i--) {
        mes->id[i] = glm_messages->id;
        mes->timestamp[i] = glm_messages->timestamp;
        mes->user[i] = glm_messages->user;
        mes->text[i] = glm_messages->text;
        
        t_message_info *tmp = glm_messages;
        glm_messages = glm_messages->next;
        free(tmp);
    }
    return mes;
}
