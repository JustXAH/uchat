//
// Created by dima on 12.01.2021.
//

#include "server.h"


void mx_add_new_message(t_server *serv, t_json *json, int user_index) {
    cJSON *MESSAGE_ID = NULL;
    char *send_str = NULL;
    json->SEND = cJSON_CreateObject();
    json->CHAT_ID = cJSON_GetObjectItemCaseSensitive(json->USER_JSON,"CHAT_ID");
    json->MESSAGE = cJSON_GetObjectItemCaseSensitive(json->USER_JSON,"MESSAGE");
    json->USER_ID = cJSON_GetObjectItemCaseSensitive(json->USER_JSON,"USER_ID");


    MESSAGE_ID = cJSON_CreateNumber(mx_db_create_new_message(serv->db, json->USER_ID->valueint, json->CHAT_ID->valueint, json->MESSAGE->valuestring));
    json->RESULT = MESSAGE_ID == NULL ? cJSON_CreateFalse() : cJSON_CreateTrue();

    json->TYPE = cJSON_CreateNumber(NEW_MESSAGE);
    cJSON_AddItemToObject(json->SEND, "CHAT_ID", json->CHAT_ID);

    if (cJSON_IsFalse(json->RESULT)) {

        cJSON_AddItemToObject(json->SEND, "TYPE", json->TYPE);
        cJSON_AddItemToObject(json->SEND, "RESULT", json->RESULT);
    }
    else {
        cJSON_AddItemToObject(json->SEND, "TYPE", json->TYPE);
        cJSON_AddItemToObject(json->SEND, "RESULT", json->RESULT);
        cJSON_AddItemToObject(json->SEND, "MESSAGE", json->MESSAGE);
        cJSON_AddItemToObject(json->SEND, "USER_ID", json->USER_ID);
    }
    send_str = cJSON_Print(json->SEND);
    write(serv->user_socket[user_index], send_str, strlen(send_str));
}
