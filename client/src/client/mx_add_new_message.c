//
// Created by Dima Voichuck on 1/25/21.
//

#include "client.h"

extern t_client_st cl_listener;

static char *get_time(long time) {
    char *time_str = NULL;
    time_t time_2 = time;

    time_str = mx_substr(ctime(&(time_2)), 12, 16);
    return time_str;
}

static void add_in_user_message(t_json *json, t_user *user, int count) {
    char *time_str;
    int i = count - 1;
    time_str = get_time(json->MESSAGE_TIME->valueint);
    bool f = false;

    if (json->USER_ID->valueint == cl_listener.my_id)
        f = true;
    mx_printint(json->MESSAGE_ID->valueint);
    mb_msg_buffer_add(json->MESSAGE_ID->valueint,   json->CHAT_ID->valueint, 
                        json->USER_ID->valueint,    "lol", 
                        time_str,                   json->MESSAGE->valuestring,
                        f);
}

void mx_add_new_message(t_system *sys, t_user *user, t_json *json) {
//    m_printstr("")
    json->RESULT = cJSON_GetObjectItemCaseSensitive(json->SERVER_JSON, "RESULT");
    if (cJSON_IsFalse(json->RESULT)) {
        // Error
    }
    else {
        json->CHAT_ID = cJSON_GetObjectItemCaseSensitive(json->SERVER_JSON, "CHAT_ID");
        json->MESSAGE_ID = cJSON_GetObjectItemCaseSensitive(json->SERVER_JSON, "MESSAGE_ID");
        json->MESSAGE = cJSON_GetObjectItemCaseSensitive(json->SERVER_JSON, "MESSAGE");
        json->MESSAGE_TIME = cJSON_GetObjectItemCaseSensitive(json->SERVER_JSON, "MESSAGE_TIME");
        json->USER_ID = cJSON_GetObjectItemCaseSensitive(json->SERVER_JSON, "USER_ID");
        json->CONTACT_ID = cJSON_GetObjectItemCaseSensitive(json->SERVER_JSON, "CONTACT_ID");
        add_in_user_message(json, user, json->COUNT_MESSAGES_ARR->valueint);
    }
}
