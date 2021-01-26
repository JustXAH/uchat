//
// Created by dima on 12.01.2021.
//

#include "server.h"


void mx_add_new_message(t_server *serv, t_json *json, int user_index) {
    char *send_str = NULL;

    json->USER_ID = cJSON_GetObjectItemCaseSensitive(json->USER_JSON,"USER_ID");
    json->CHAT_ID = cJSON_GetObjectItemCaseSensitive(json->USER_JSON,"CHAT_ID");
    json->MESSAGE = cJSON_GetObjectItemCaseSensitive(json->USER_JSON,"MESSAGE");

    json->SEND = cJSON_CreateObject();
    json->TYPE = cJSON_CreateNumber(NEW_MESSAGE);

    cJSON_AddItemToObject(json->SEND, "TYPE", json->TYPE);
    cJSON_AddItemToObject(json->SEND, "RESULT", json->RESULT);

    json->MESSAGE_ID = cJSON_CreateNumber(mx_db_create_new_message(serv->db, json->USER_ID->valueint, json->CHAT_ID->valueint, json->MESSAGE->valuestring));

    if (json->MESSAGE_ID->valueint == 0) {
        json->RESULT = cJSON_CreateFalse();

    }
    else {
        json->RESULT = cJSON_CreateTrue();
        cJSON_AddItemToObject(json->SEND, "MESSAGE_ID", json->MESSAGE_ID);
    }

    send_str = cJSON_Print(json->SEND);
    write(1, send_str, strlen(send_str));

    write(serv->user_socket[user_index], send_str, strlen(send_str));

    cJSON_Delete(json->SEND);
    free(send_str);
}
