//
// Created by dima on 12.01.2021.
//

#include "server.h"

void mx_add_new_message(t_server *serv, t_json *json) {
    cJSON *NEW_MESSAGES = cJSON_CreateObject();
    cJSON *MESSAGES_ID = NULL;

    char *send = NULL;

    MESSAGES_ID = cJSON_CreateNumber(mx_db_create_new_message(serv->db, json->USER_ID->valueint, json->CHAT_ID->valueint, json->MESSAGE->valuestring));
    json->RESULT = MESSAGES_ID == NULL ? cJSON_CreateFalse() : cJSON_CreateTrue();

    cJSON_AddItemToObject(NEW_MESSAGES, "TYPE", json->TYPE);
    cJSON_AddItemToObject(NEW_MESSAGES, "CHAT_ID", json->CHAT_ID);
    cJSON_AddItemToObject(NEW_MESSAGES, "RESULT", json->RESULT);
    cJSON_AddItemToObject(NEW_MESSAGES, "MESSAGES_ID", MESSAGES_ID);
    cJSON_AddItemToObject(NEW_MESSAGES, "MESSAGES", json->MESSAGE);

    send = cJSON_Print(NEW_MESSAGES);

//    write(user_sock, send, strlen(send));

    cJSON_Delete(NEW_MESSAGES);
    free(send);
}
