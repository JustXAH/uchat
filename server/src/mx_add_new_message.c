//
// Created by dima on 12.01.2021.
//

#include "server.h"

static void which_user_online(t_server *serv, t_json *json, char *send_str) {
    int contact_id = json->CONTACT_ID->valueint;

    for (int i = 0; serv->users_id[i]; i++)
        if (serv->users_id[i] == contact_id)
            write(serv->user_socket[i], send_str, strlen(send_str));
}

void mx_add_new_message(t_server *serv, t_json *json, int user_index) {
    char *send_str = NULL;


    json->USER_ID = cJSON_GetObjectItemCaseSensitive(json->USER_JSON,"USER_ID");
    json->CHAT_ID = cJSON_GetObjectItemCaseSensitive(json->USER_JSON,"CHAT_ID");
    json->MESSAGE = cJSON_GetObjectItemCaseSensitive(json->USER_JSON,"MESSAGE");
    json->CONTACT_ID = cJSON_GetObjectItemCaseSensitive(json->USER_JSON,"CONTACT_ID");

    json->SEND = cJSON_CreateObject();
    json->TYPE = cJSON_CreateNumber(NEW_MESSAGE);

    cJSON_AddItemToObject(json->SEND, "TYPE", json->TYPE);
    cJSON_AddItemToObject(json->SEND, "RESULT", json->RESULT);

    json->MESSAGE_ID = cJSON_CreateNumber(mx_db_create_new_message(serv->db, json->USER_ID->valueint, json->CHAT_ID->valueint, json->MESSAGE->valuestring));
    
    t_message_info *message_info = mx_db_get_message(serv->db, json->MESSAGE_ID->valueint);

    cJSON *USER_ID = cJSON_CreateNumber(message_info->user);
    cJSON *CHAT_ID = cJSON_CreateNumber(json->CHAT_ID->valueint);
    cJSON *MESSAGE_ID = cJSON_CreateNumber(message_info->id);
    cJSON *MESSAGE = cJSON_CreateString(message_info->text);
    cJSON *MESSAGE_TIME =  cJSON_CreateNumber(message_info->timestamp);
    cJSON *CONTACT_ID = cJSON_CreateNumber(json->CONTACT_ID->valueint);
    cJSON *NOTIFICATION = cJSON_CreateNumber(1);

    if (json->MESSAGE_ID->valueint == 0) {
        json->RESULT = cJSON_CreateFalse();

    }
    else {
        json->RESULT = cJSON_CreateTrue();
        cJSON_AddItemToObject(json->SEND, "MESSAGE_TIME", MESSAGE_TIME);
        cJSON_AddItemToObject(json->SEND, "MESSAGE_ID", MESSAGE_ID);
        cJSON_AddItemToObject(json->SEND, "MESSAGE", MESSAGE);
        cJSON_AddItemToObject(json->SEND, "CHAT_ID", CHAT_ID);
        cJSON_AddItemToObject(json->SEND, "USER_ID", USER_ID);
        cJSON_AddItemToObject(json->SEND, "CONTACT_ID", CONTACT_ID);
        cJSON_AddItemToObject(json->SEND, "NOTIFICATION", NOTIFICATION);
    }

    send_str = cJSON_Print(json->SEND);

    write(serv->user_socket[user_index], send_str, strlen(send_str));
    which_user_online(serv, json, send_str);

    cJSON_Delete(json->SEND);
    free(send_str);
}
