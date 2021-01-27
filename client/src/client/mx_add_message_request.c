//
// Created by Dima Voichuck on 1/25/21.
//

#include "client.h"

void mx_add_message_request(t_system *sys, t_user *user, t_json *json, char *messages_str, int chat_id, int contact_id) {
    char *send_str = NULL;

    json->SEND = cJSON_CreateObject();
    json->TYPE = cJSON_CreateNumber(NEW_MESSAGE);

    json->USER_ID = cJSON_CreateNumber(user->my_id);
    json->CONTACT_ID = cJSON_CreateNumber(contact_id);
    json->CHAT_ID = cJSON_CreateNumber(chat_id);
    json->MESSAGE = cJSON_CreateString(messages_str);

    cJSON_AddItemToObject(json->SEND, "TYPE", json->TYPE);
    cJSON_AddItemToObject(json->SEND, "USER_ID", json->USER_ID);
    cJSON_AddItemToObject(json->SEND, "CHAT_ID", json->CHAT_ID);
    cJSON_AddItemToObject(json->SEND, "MESSAGE", json->MESSAGE);
    cJSON_AddItemToObject(json->SEND, "CONTACT_ID", json->CONTACT_ID);

    send_str = cJSON_Print(json->SEND);

    write(sys->sockfd, send_str, strlen(send_str));

    free(send_str);
    cJSON_Delete(json->SEND);
}