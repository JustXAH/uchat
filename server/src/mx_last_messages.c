//
// Created by dima on 17.01.2021.
//

#include "server.h"

void mx_last_messages(t_server *serv, t_json *json, int user_index) {
    char *send_str = NULL;
    t_message *message = mx_db_get_last_messages(serv->db, json->CHAT_ID->valueint);

    json->TYPE = cJSON_CreateNumber(LAST_MESSAGES);

    if (message == NULL) {
        json->RESULT = cJSON_CreateFalse();
    }
    else {
        json->RESULT = cJSON_CreateTrue();
        json->SEND = cJSON_CreateObject();
        json->MESSAGES_ARR = cJSON_CreateStringArray((const char *const *) message->text, message->count);
        json->COUNT_MESSAGES_ARR = cJSON_CreateNumber(message->count);
        json->MESSAGES_ID = cJSON_CreateIntArray(message->id, message->count);
        json->MESSAGES_TIME = cJSON_CreateIntArray((const int *) message->timestamp, message->count);
        json->SENDER_ID = cJSON_CreateIntArray(message->user, message->count);
        json->USER_NAME = cJSON_CreateString("login");

        cJSON_AddItemToObject(json->SEND, "MESSAGES_ARR", json->MESSAGES_ARR);
        cJSON_AddItemToObject(json->SEND, "COUNT_MESSAGES_ARR", json->COUNT_MESSAGES_ARR);
        cJSON_AddItemToObject(json->SEND, "MESSAGE_ID", json->MESSAGES_ID);
        cJSON_AddItemToObject(json->SEND, "MESSAGES_TIME", json->MESSAGES_TIME);
        cJSON_AddItemToObject(json->SEND, "SENDER_ID", json->SENDER_ID);
        cJSON_AddItemToObject(json->SEND, "USER_NAME", json->USER_NAME);

    }
    cJSON_AddItemToObject(json->SEND, "TYPE", json->TYPE);

    send_str = cJSON_Print(json->SEND);
    //send string-JSON to client

//    write(user_sock, send_str, strlen(send_str));
    write(serv->user_socket[user_index], send_str, strlen(send_str));

    cJSON_Delete(json->SEND);
    free(send_str);
}
