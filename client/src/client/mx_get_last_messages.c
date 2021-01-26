//
// Created by Dima Voichuck on 1/25/21.
//

#include "client.h"


static char *get_time(long time) {
    char *time_str = NULL;
    time_t time_2 = time;

    time_str = mx_substr(ctime(&(time_2)), 4, 16);
    return time_str;
}

static void add_in_user_message(t_json *json, t_user *user, int count) {
    char *time_str;
    int i = count - 1;

    time_str = get_time(cJSON_GetArrayItem(json->MESSAGES_TIME, i)->valueint);
    mb_msg_buffer_add(cJSON_GetArrayItem(json->MESSAGES_ID, i)->valueint, json->CHAT_ID->valueint,
                      cJSON_GetArrayItem(json->USER_ID, i)->valueint,
                      cJSON_GetArrayItem(json->USER_NAME, i)->valuestring,
                      time_str, cJSON_GetArrayItem(json->MESSAGES_ARR, i)->valuestring);
}

void mx_get_last_messages(t_system *sys, t_user *user, t_json *json) {
    json->RESULT = cJSON_GetObjectItemCaseSensitive(json->SERVER_JSON, "RESULT");
    if (cJSON_IsFalse(json->RESULT)) {
        // Error
    }
    else {
        json->CHAT_ID = cJSON_GetObjectItemCaseSensitive(json->SERVER_JSON, "CHAT_ID");
        json->MESSAGES_ARR = cJSON_GetObjectItemCaseSensitive(json->SERVER_JSON, "MESSAGES_ARR");
        json->COUNT_MESSAGES_ARR = cJSON_GetObjectItemCaseSensitive(json->SERVER_JSON, "COUNT_MESSAGES_ARR");
        json->MESSAGES_ID = cJSON_GetObjectItemCaseSensitive(json->SERVER_JSON, "MESSAGES_ID");
        json->MESSAGES_TIME = cJSON_GetObjectItemCaseSensitive(json->SERVER_JSON, "MESSAGE_TIME");
        json->CHAT_ID = cJSON_GetObjectItemCaseSensitive(json->SENDER_ID, "SENDER_ID");
        json->USER_NAME = cJSON_GetObjectItemCaseSensitive(json->USER_NAME, "USER_NAME");
        add_in_user_message(json, user, json->COUNT_MESSAGES_ARR->valueint);
    }
}
