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
        if (!mx_strcmp(azColName[i],"Id"))
            c->id = argv[i] ? mx_atoi(argv[i]) : 0;
        if (!mx_strcmp(azColName[i],"ChatName"))
            c->chat_name = mx_strdup(argv[i]);
        if (!mx_strcmp(azColName[i],"Notification"))
            c->notification = mx_atoi(argv[i]);
//        if (!mx_strcmp(azColName[i],"Time"))
//            c->timestamp = mx_atoi(argv[i]);
    }
    printf("chat info %d: %s, %d %ld",c->id,c->chat_name,c->notification,c->timestamp);
    return 0;
}

t_chat *mx_db_get_chats_info(sqlite3 *db, int user) {
    char *err_msg = 0;
    int rc;
    ci_chat_info = NULL;
    ci_count = 0;
    char sql[1024];
    snprintf(sql, sizeof(sql),
              "SELECT Chats.Id AS Id, Login AS ChatName, Notification \
              FROM Chats JOIN Users ON Chats.User2 = Users.Id \
              WHERE User = '%d' UNION ALL \
              SELECT Chats.Id AS Id, Login AS ChatName, Notification2 AS Notification \
              FROM Chats JOIN Users ON Chats.User = Users.Id \
              WHERE User2 = '%d';",user,user);
//             "SELECT Chats.Id AS Id, Login AS ChatName, Notification, Time \
//             FROM Chats \
//             INNER JOIN Users ON Chats.User2 = Users.Id \
//             INNER JOIN (SELECT MAX(Time) AS Time, Chat FROM Messages GROUP BY Chat) AS MaxT ON Chats.Id = MaxT.Chat \
//             WHERE User = '%d' UNION ALL \
//             SELECT Chats.Id AS Id, Login AS ChatName, Notification2, Time \
//             FROM Chats \
//             INNER JOIN Users ON Chats.User = Users.Id \
//             INNER JOIN (SELECT MAX(Time) AS Time, Chat FROM Messages GROUP BY Chat) AS MaxT ON Chats.Id = MaxT.Chat \
//             WHERE User2 = '%d' ORDER BY Time;",user,user);

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
    chats->notification = (int*)malloc(ci_count * sizeof(int));
    //chats->timestamp = (time_t*)malloc(ci_count * sizeof(time_t));
    for (int i = ci_count-1; i >= 0; i--) {
        chats->id[i] = ci_chat_info->id;
        chats->chat_name[i] = ci_chat_info->chat_name;
        chats->notification[i] = ci_chat_info->notification;
        //chats->timestamp[i] = ci_chat_info->timestamp;
        t_chat_info *tmp = ci_chat_info;
        ci_chat_info = ci_chat_info->next;
        free(tmp);
    }
    return chats;
}
