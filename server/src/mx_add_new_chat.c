//
// Created by Igor Khanenko on 10.01.2021.
//

#include "server.h"

static void which_user_online(t_server *serv, t_json *json, char *send_str) {
    int contact_id = json->CONTACT_ID->valueint;

    for (int i = 0; serv->users_id[i]; i++)
        if (serv->users_id[i] == contact_id)
            write(serv->user_socket[i], send_str, strlen(send_str));
}

void add_new_chat_and_json_create(t_server *serv, t_json **json, int user_id, int user_index, bool flag) {
    t_chat *chats = NULL;
    char *send_str = NULL;
    int answer = mx_db_get_chat_by_users(serv->db, (*json)->CONTACT_ID->valueint, (*json)->USER_ID->valueint);

    if (answer == 0)
        answer = mx_db_create_new_chat(serv->db, (*json)->USER_ID->valueint, (*json)->CONTACT_ID->valueint);
    if (answer == -1) {
        (*json)->RESULT = cJSON_CreateFalse();;
    }
    else {
        (*json)->RESULT = cJSON_CreateTrue();
        chats = mx_db_get_chats_info(serv->db, user_id);
        (*json)->CHATS_ID_ARR = cJSON_CreateIntArray(chats->id, chats->count);
        (*json)->CHATS_NAME_ARR = cJSON_CreateStringArray((const char * const*)chats->chat_name, chats->count);
    }
    cJSON_AddItemToObject((*json)->SEND, "RESULT", (*json)->RESULT);
    cJSON_AddItemToObject((*json)->SEND, "CHATS_ID_ARR", (*json)->CHATS_ID_ARR);
    cJSON_AddItemToObject((*json)->SEND, "CHATS_NAME_ARR", (*json)->CHATS_NAME_ARR);

    send_str = cJSON_Print((*json)->SEND);

    if (flag == true)
        write(serv->user_socket[user_index], send_str, strlen(send_str));
    else
        which_user_online(serv, (*json), send_str);

    cJSON_Delete((*json)->SEND);
    free(send_str);

    if (MALLOC_SIZE(chats->id)) {
        free(chats->id);
    }
    if (MALLOC_SIZE(chats->chat_name)) {
        //Shit be segfaulting as well
        //mx_del_strarr(&chats->chat_name);
    }
    free(chats);

}

void mx_add_new_chat(t_server *serv, t_json *json, int user_index) {
    json->USER_ID = cJSON_GetObjectItemCaseSensitive(json->USER_JSON, "USER_ID");
    json->CONTACT_ID = cJSON_GetObjectItemCaseSensitive(json->USER_JSON, "CONTACT_ID");
    json->SEND = cJSON_CreateObject();
    json->TYPE = cJSON_CreateNumber(NEW_CHAT);

    cJSON_AddItemToObject(json->SEND, "TYPE", json->TYPE);
    add_new_chat_and_json_create(serv, &json, json->USER_ID->valueint, user_index, true);

    json->SEND = cJSON_CreateObject();
    json->TYPE = cJSON_CreateNumber(NEW_CHAT);

    cJSON_AddItemToObject(json->SEND, "TYPE", json->TYPE);
    add_new_chat_and_json_create(serv, &json, json->CONTACT_ID->valueint, user_index, false);

}
