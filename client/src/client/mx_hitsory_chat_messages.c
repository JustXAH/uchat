//
// Created by Dima Voichuck on 1/26/21.
//


#include "client.h"

extern t_client_st cl_listener;

static void add_in_user_message(t_json *json, t_user *user, int count) {
    if (count < 1)
        return;
    char **time_str = mx_strsplit(json->MESSAGES_TIME->valuestring, '~');
    bool f = false;

    for (int i = 0; i < count; i++) {
        if (cJSON_GetArrayItem(json->SENDER_ID, i)->valueint == cl_listener.my_id)
            f = true;
        mb_msg_buffer_add(cJSON_GetArrayItem(json->MESSAGES_ID, i)->valueint,
                          cl_listener.chat_in_focus,
                          cJSON_GetArrayItem(json->SENDER_ID, i)->valueint,
                          "lol",
                          time_str[i], 
                          cJSON_GetArrayItem(json->MESSAGES_ARR, i)->valuestring, f);
        free(time_str[i]);
        f = false;
    }
    free(time_str);
}

void mx_get_history_chat(t_system *sys, t_user *user, t_json *json) {
    json->RESULT = cJSON_GetObjectItemCaseSensitive(json->SERVER_JSON, "RESULT");
    mx_remove_notification_request(sys, json, user, cl_listener.chat_in_focus, user->my_id);
    if (cJSON_IsFalse(json->RESULT)) {
        // Error
    }
    else {
        json->MESSAGES_ARR = cJSON_GetObjectItemCaseSensitive(json->SERVER_JSON, "MESSAGES_ARR");
        json->COUNT_MESSAGES_ARR = cJSON_GetObjectItemCaseSensitive(json->SERVER_JSON, "COUNT_MESSAGES_ARR");
        mx_printstr("his 1\n");
        json->MESSAGES_ID = cJSON_GetObjectItemCaseSensitive(json->SERVER_JSON, "MESSAGES_ID");
        mx_printstr("his 2\n");
        json->MESSAGES_TIME = cJSON_GetObjectItemCaseSensitive(json->SERVER_JSON, "MESSAGES_TIME");
        mx_printstr("his 3\n");
        json->SENDER_ID = cJSON_GetObjectItemCaseSensitive(json->SERVER_JSON, "SENDER_ID");
        mx_printstr("his 3\n");
        //json->USER_NAME = cJSON_GetObjectItemCaseSensitive(json->USER_NAME, "USER_NAME");
        add_in_user_message(json, user, json->COUNT_MESSAGES_ARR->valueint);
    }
    mx_printstr("history recieved and loaded into buffer\n");
}
