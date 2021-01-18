//
// Created by dima on 12.01.2021.
//

#include "server.h"

void mx_add_new_message(t_server *serv, t_json *json) {
    char *send = NULL;
    cJSON *MESSAGE_ID = NULL;

    MESSAGE_ID = cJSON_CreateNumber(mx_db_create_new_message(serv->db, json->USER_ID->valueint, json->CHAT_ID->valueint, json->MESSAGE->valuestring));
    json->RESULT = MESSAGE_ID == NULL ? cJSON_CreateFalse() : cJSON_CreateTrue();

    cJSON_AddItemToObject(json->SEND, "CHAT_ID", json->CHAT_ID);
    cJSON_AddItemToObject(json->SEND, "RESULT", json->RESULT);

    mx_last_messages(serv, json);
}
