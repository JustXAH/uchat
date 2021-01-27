//
// Created by Dima Voichuck on 1/26/21.
//

#include "client.h"

void mx_get_history_chat_request(t_system *sys, t_user *user, t_json *json, int chat_id) {
    char *send_str = NULL;

    json->SEND = cJSON_CreateObject();
    json->TYPE = cJSON_CreateNumber(HISTORY_CHAT);

    json->USER_ID = cJSON_CreateNumber(user->my_id);
    json->CHAT_ID = cJSON_CreateNumber(chat_id);

    cJSON_AddItemToObject(json->SEND, "TYPE", json->TYPE);
    cJSON_AddItemToObject(json->SEND, "USER_ID", json->USER_ID);
    cJSON_AddItemToObject(json->SEND, "CHAT_ID", json->CHAT_ID);

    send_str = cJSON_Print(json->SEND);

    write(sys->sockfd, send_str, strlen(send_str));

    free(send_str);
    cJSON_Delete(json->SEND);
}
