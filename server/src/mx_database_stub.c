//
// Created by Igor Khanenko on 1/2/21.
//

#include "server.h"

cJSON *mx_database_stub(cJSON *user) {
    cJSON *SEND = cJSON_CreateObject();
    cJSON *TYPE = NULL;
    cJSON *RESULT = NULL; //результат аутентификации: FALSE - неудачно, TRUE - успешно
    cJSON *MESSAGE = NULL;

    cJSON *USER_TYPE = cJSON_GetObjectItemCaseSensitive(user, "TYPE");
    cJSON *LOGIN = cJSON_GetObjectItemCaseSensitive(user, "LOGIN");
    cJSON *PASS = cJSON_GetObjectItemCaseSensitive(user, "PASS");

    if (USER_TYPE->valueint == 3) { //пришел запрос на регистрацию
        TYPE = cJSON_CreateNumber(3); //тип связи клиент-сервер (3- регистрация)
        if (mx_strcmp(LOGIN->valuestring, "XAH") != 0) {
            RESULT = cJSON_CreateTrue();
            MESSAGE = cJSON_CreateString("Congratulations on your successful G-Chat account registration!");
            }
        else {
            RESULT = cJSON_CreateFalse();
            MESSAGE = cJSON_CreateString("Whoops, such an account already exists!/nPlease try another username.");
        }
    }
    else { //пришел запрос на log in (аутентификацию логина и пароля)
        TYPE = cJSON_CreateNumber(2); //тип связи клиент-сервер (2 - аутентификация)
        if (mx_strcmp(LOGIN->valuestring, "XAH") == 0) {
            if (mx_strcmp(PASS->valuestring, "123") == 0) {
                RESULT = cJSON_CreateTrue();
                MESSAGE = cJSON_CreateString("Login and password are correct");
//            answer = mx_strdup("LOGIN and PASSword are correct");
            } else {
                RESULT = cJSON_CreateFalse();
                MESSAGE = cJSON_CreateString("Invalid password");
//            answer = mx_strdup("Invalid PASSword");
            }
        } else {
            RESULT = cJSON_CreateFalse();
            MESSAGE = cJSON_CreateString("Invalid login");
//        answer = mx_strdup("Invalid LOGIN");
        }
    }

    cJSON_AddItemToObject(SEND, "TYPE", TYPE);
    cJSON_AddItemToObject(SEND, "RESULT", RESULT);
    cJSON_AddItemToObject(SEND, "MESSAGE", MESSAGE);
//    cJSON_AddItemToObject(AUTHENTICATION, "sender", sender);

    return SEND;
}
