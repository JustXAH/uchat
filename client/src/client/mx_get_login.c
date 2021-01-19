
//
// Created by dima on 15.01.2021.
//

#include "client.h"

void mx_get_login(t_system *sys, t_user *user, t_json *json) {
    json->RESULT = cJSON_GetObjectItemCaseSensitive(json->SERVER_JSON, "RESULT");
    json->FOUND_LOGIN = cJSON_GetObjectItemCaseSensitive(json->SERVER_JSON, "FOUND_LOGIN");

    if (cJSON_IsFalse(json->RESULT)) {
        // error func
    }
    else {
        sys->found_username = mx_strdup(json->FOUND_LOGIN->valuestring);
    }
}