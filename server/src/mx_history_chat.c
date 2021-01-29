//
// Created by dima on 17.01.2021.
//

#include "server.h"

static char *get_time(long time_mess) {
    char *time_str = NULL;
    time_t time_2 = time_mess;
    long int time_3 = time(NULL);

    if ((time_3 - time_mess) > 86400) {
        time_str = mx_substr(ctime(&(time_2)), 4, 16);
    }
    else
        time_str = mx_substr(ctime(&(time_2)), 11, 16);
    return time_str;
}

void mx_history_chat(t_server *serv, t_json *json, int user_index) {
    char *send_str = NULL;
    json->CHAT_ID = cJSON_GetObjectItemCaseSensitive(json->USER_JSON,"CHAT_ID");

    t_message *message = mx_db_get_last_messages(serv->db, json->CHAT_ID->valueint);
    char *tmp = NULL;
    char *tmp1 = NULL;
    char *tbuf = NULL;
    for (int i = 0; i < message->count; i++) {
        tbuf = get_time(message->timestamp[i]);
        tmp1 = tmp;
        tmp = mx_strjoin(tmp, tbuf);
        free(tmp1);
        tmp1 = tmp;
        tmp = mx_strjoin(tmp, "~");
        free(tmp1);
        free(tbuf);
    }
    json->SEND = cJSON_CreateObject();
    json->TYPE = cJSON_CreateNumber(HISTORY_CHAT);

    if (message == NULL) {
        json->RESULT = cJSON_CreateFalse();
    }
    else {
        json->RESULT = cJSON_CreateTrue();
        json->SEND = cJSON_CreateObject();
        json->MESSAGES_ARR = cJSON_CreateStringArray((const char *const *) message->text, message->count);
        json->COUNT_MESSAGES_ARR = cJSON_CreateNumber(message->count);
        json->MESSAGES_ID = cJSON_CreateIntArray(message->id, message->count);

        
        json->SENDER_ID = cJSON_CreateIntArray(message->user, message->count);

        cJSON_AddItemToObject(json->SEND, "MESSAGES_ARR", json->MESSAGES_ARR);
        cJSON_AddItemToObject(json->SEND, "COUNT_MESSAGES_ARR", json->COUNT_MESSAGES_ARR);
        cJSON_AddItemToObject(json->SEND, "MESSAGES_ID", json->MESSAGES_ID);
        cJSON_AddItemToObject(json->SEND, "MESSAGES_TIME", cJSON_CreateString(tmp));
        cJSON_AddItemToObject(json->SEND, "SENDER_ID", json->SENDER_ID);
    }
    cJSON_AddItemToObject(json->SEND, "RESULT", json->RESULT);
    cJSON_AddItemToObject(json->SEND, "TYPE", json->TYPE);
    send_str = cJSON_Print(json->SEND);

    write(serv->user_socket[user_index], send_str, strlen(send_str));

    cJSON_Delete(json->SEND);
    free(send_str);
    if(tmp)
        free(tmp);
}
