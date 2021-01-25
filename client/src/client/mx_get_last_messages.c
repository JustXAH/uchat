//
// Created by Dima Voichuck on 1/25/21.
//

#include "client.h"

static void get_time(t_json *json, int count) {
    char **time_str = (char **)malloc(sizeof(char *) * count);
    long time = 0;
    time_t time_2 = 0;

    for (int i = 0; i < count; i++)
        time_str[i] = NULL;
    for (int i = 0; time_str[i]; i++) {
        time = cJSON_GetArrayItem(json->MESSAGES_TIME, i)->valueint;
        time_2 = time;
        time_str[i] = mx_substr(ctime(&(time_2)), 4, 16);
    }
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
    }
}
