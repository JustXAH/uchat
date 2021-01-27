//
// Created by mac on 08.01.2021.
//

#include "server.h"

t_message_info *gm_mes_info;

static int get_message_callback(void *NotUsed, int argc, char **argv, char **azColName) {

    NotUsed = 0;
    for (int i = 0; i < argc; i++) {
        if (!mx_strcmp(azColName[i],"Id"))
            gm_mes_info->id = argv[i] ? mx_atoi(argv[i]) : 0;
        if (!mx_strcmp(azColName[i],"User"))
            gm_mes_info->user = argv[i] ? mx_atoi(argv[i]) : 0;
        if (!mx_strcmp(azColName[i],"Text"))
            gm_mes_info->text = mx_strdup(argv[i]);
        if (!mx_strcmp(azColName[i],"Time"))
            gm_mes_info->timestamp = mx_atoi(argv[i]);
    }
    return 0;
}

t_message_info *mx_db_get_message(sqlite3 *db, int mes_id) {
    char *err_msg = 0;
    int rc;
    char sql[1024];
    gm_mes_info = (t_message_info*) malloc (sizeof(t_message_info));
    gm_mes_info->next = NULL;
    snprintf(sql, sizeof(sql),
             "SELECT Id, User, Text, Time FROM Messages WHERE Id = '%d';",mes_id);
    rc = sqlite3_exec(db, sql, get_message_callback, 0, &err_msg);
    if (rc != SQLITE_OK ) {
        fprintf(stderr, "Failed to select data\n");
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
        free(gm_mes_info);
        gm_mes_info = NULL;
    }

    return gm_mes_info;
}
