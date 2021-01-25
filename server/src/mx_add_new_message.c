//
// Created by dima on 12.01.2021.
//

#include "server.h"


void mx_add_new_message(t_server *serv, t_json *json, int user_index) {
    char *send = NULL;
    cJSON *MESSAGE_ID = NULL;
    char *send_str = NULL;



    MESSAGE_ID = cJSON_CreateNumber(mx_db_create_new_message(serv->db, json->USER_ID->valueint, json->CHAT_ID->valueint, json->MESSAGE->valuestring));
    json->RESULT = MESSAGE_ID == NULL ? cJSON_CreateFalse() : cJSON_CreateTrue();

    cJSON_AddItemToObject(json->SEND, "CHAT_ID", json->CHAT_ID);

    if (cJSON_IsFalse(json->RESULT)) {
        json->SEND = cJSON_CreateObject();
        json->TYPE = cJSON_CreateNumber(LAST_MESSAGES);

        cJSON_AddItemToObject(json->SEND, "TYPE", json->TYPE);
        cJSON_AddItemToObject(json->SEND, "RESULT", json->RESULT);

        send_str = cJSON_Print(json->SEND);
        write(serv->user_socket[user_index], send_str, strlen(send_str));
    }
    else
        mx_last_messages(serv, json, serv->user_socket[user_index]);
}
