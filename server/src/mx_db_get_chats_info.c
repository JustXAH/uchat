#include "server.h"

t_chat_info *ci_chat_info;
int ci_count;

static int get_chats_info_callback(void *NotUsed, int argc, char **argv, char **azColName) {
    t_chat_info *c = (t_chat_info*)malloc(sizeof(t_chat_info));
    c->next = ci_chat_info;
    ci_chat_info = c;
    ci_count++;
    NotUsed = 0;
    for (int i = 0; i < argc; i++) {
        if (!mx_strcmp(azColName[i],"User"))
            c->id = argv[i] ? mx_atoi(argv[i]) : 0;
        if (!mx_strcmp(azColName[i],"ChatName"))
            c->chat_name = mx_strdup(argv[i]);
    }
    return 0;
}

t_chat *mx_db_get_chats_info(sqlite3 *db, int user) {
    char *err_msg = 0;
    int rc;
    ci_chat_info = NULL;
    ci_count = 0;
    char sql[1024];
    snprintf(sql, sizeof(sql),
             "SELECT User2 As User, Login AS ChatName \
             FROM Chats JOIN Users ON Chats.User2 = Users.Id \
             WHERE User = '%d' UNION ALL \
             SELECT User, Login AS ChatName \
             FROM Chats JOIN Users ON Chats.User = Users.Id \
             WHERE User2 = '%d';",user,user);
    rc = sqlite3_exec(db, sql, get_chats_info_callback, 0, &err_msg);
    if (rc != SQLITE_OK ) {
        fprintf(stderr, "Failed to select data\n");
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
    }
    t_chat *chats = (t_chat*)malloc(sizeof(t_chat));
    chats->count = ci_count;
    chats->id = (int*)malloc(ci_count * sizeof(int));
    chats->chat_name = (char**)malloc(ci_count * sizeof(char*));
    for (int i = ci_count-1; i >= 0; i--) {
        chats->id[i] = ci_chat_info->id;
        chats->chat_name[i] = ci_chat_info->chat_name;
        t_chat_info *tmp = ci_chat_info;
        ci_chat_info = ci_chat_info->next;
        free(tmp);
    }
    return chats;
}
