//
// Created by Igor Khanenko on 1/2/21.
//

#include "server.h"

cJSON *mx_database_stub(cJSON *user) {
    cJSON *AUTHENTICATION = cJSON_CreateObject();
    cJSON *TYPE = cJSON_CreateNumber(2); //тип связи клиент-сервер (2 - аутентификация)
    cJSON *RESULT = NULL; //результат аутентификации: FALSE - неудачно, TRUE - успешно
    cJSON *MESSAGE = NULL;
//    cJSON *sender = cJSON_CreateString("server");
    cJSON *LOGIN = cJSON_GetObjectItemCaseSensitive(user, "LOGIN");
    cJSON *PASS = cJSON_GetObjectItemCaseSensitive(user, "PASS");

    if (mx_strcmp(LOGIN->valuestring, "XAH") == 0) {
        if (mx_strcmp(PASS->valuestring, "123") == 0) {
            RESULT = cJSON_CreateTrue();
            MESSAGE = cJSON_CreateString("LOGIN and PASSword are correct");
//            answer = mx_strdup("LOGIN and PASSword are correct");
        }
        else {
            RESULT = cJSON_CreateFalse();
            MESSAGE = cJSON_CreateString("Invalid PASSword");
//            answer = mx_strdup("Invalid PASSword");
        }
    }
    else {
        RESULT = cJSON_CreateFalse();
        MESSAGE = cJSON_CreateString("Invalid LOGIN");
//        answer = mx_strdup("Invalid LOGIN");
    }

    cJSON_AddItemToObject(AUTHENTICATION, "TYPE", TYPE);
    cJSON_AddItemToObject(AUTHENTICATION, "RESULT", RESULT);
    cJSON_AddItemToObject(AUTHENTICATION, "MESSAGE", MESSAGE);
//    cJSON_AddItemToObject(AUTHENTICATION, "sender", sender);

    return AUTHENTICATION;
}
