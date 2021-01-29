//
// Created by Dima Voichuck on 1/28/21.
//

#include "client.h"

void mx_remove_notification_request(t_system *sys, t_json *json, t_user *user, int chat_id, int user_id) {
    char *send_str = NULL;
    cJSON *SEND = cJSON_CreateObject();
    cJSON *TYPE = cJSON_CreateNumber(REMOVE_NOTIFICATION);
    cJSON *CHAT_ID = cJSON_CreateNumber(chat_id);
    cJSON *USER_ID = cJSON_CreateNumber(user_id);

    cJSON_AddItemToObject(SEND, "TYPE", TYPE);
    cJSON_AddItemToObject(SEND, "CHAT_ID", CHAT_ID);
    cJSON_AddItemToObject(SEND, "USER_ID", USER_ID);

    send_str = cJSON_Print(SEND);
    write(sys->sockfd, send_str, strlen(send_str));
}