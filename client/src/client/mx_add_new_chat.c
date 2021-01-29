//
// Created by dima on 15.01.2021.
//

#include "client.h"

extern t_client_st cl_listener;
extern t_chat *chat;

static void add_chats_login(t_user *user, cJSON *CHATS_NAME_ARR) {
    user->chats_name = (char **)malloc(sizeof(char *) * (user->chats_count + 1));
    for (int i = 0; i != user->chats_count; i++) {
        user->chats_name[i] = mx_strdup(cJSON_GetArrayItem(CHATS_NAME_ARR, i)->valuestring);
    }
    user->chats_name[user->chats_count] = NULL;
}

static void add_chats_id(t_user *user, cJSON *CHATS_ID_ARR) {
    user->chats_id = (int *)malloc(sizeof(int) * user->chats_count);
    for (int i = 0; i != user->chats_count; i++) {
        user->chats_id[i] = cJSON_GetArrayItem(CHATS_ID_ARR, i)->valueint;
    }
}

void mx_add_new_chat(t_system *sys, t_user *user, t_json *json) {

        json->RESULT = cJSON_GetObjectItemCaseSensitive(json->SERVER_JSON, "RESULT");
        json->CHATS_ID_ARR = cJSON_GetObjectItemCaseSensitive(json->SERVER_JSON, "CHATS_ID_ARR");
        json->CHATS_NAME_ARR = cJSON_GetObjectItemCaseSensitive(json->SERVER_JSON, "CHATS_NAME_ARR");


        if (cJSON_IsFalse(json->RESULT)) {
            // вызов всплывающего текста c ошибкой
        }
        else {
            user->chats_count = cJSON_GetArraySize(json->CHATS_NAME_ARR);
            if (MALLOC_SIZE(user->chats_id)) {
                free(user->chats_id);
            }
            add_chats_id(user, json->CHATS_ID_ARR);
            if (MALLOC_SIZE(user->chats_name)) {
                free(user->chats_name);
            }
            add_chats_login(user, json->CHATS_NAME_ARR);
        }
        cJSON_DeleteItemFromObject(json->SERVER_JSON, "RESULT");
        cJSON_DeleteItemFromObject(json->SERVER_JSON, "CHATS_COUNT");
        cJSON_DeleteItemFromObject(json->SERVER_JSON, "CHATS_ID_ARR");
        cJSON_DeleteItemFromObject(json->SERVER_JSON, "CHATS_NAME_ARR");

    //cl_listener.new_contact_received = true;
    mx_printstr("recieved new chat id\n");
    
}
