//
// Created by mac on 12.01.2021.
//

#include "server.h"

void mx_get_login(t_server *serv, int user_id, int user_sock) {
    cJSON *SEND = cJSON_CreateObject();
    cJSON *TYPE = cJSON_CreateNumber(GET_LOGIN);
    cJSON *RESULT = NULL; //результат аутентификации: FALSE - неудачно, TRUE - успешно
    cJSON *LOGIN = NULL;
    char *send_str = NULL;

    LOGIN = cJSON_CreateString(mx_db_get_login(serv->db, user_id));
    if (LOGIN->string == NULL) {
        RESULT = cJSON_CreateFalse(); // ошибка при регистрации - логин уже существует
    }
    else {
        RESULT = cJSON_CreateTrue(); //регистрация прошла успешно
    }

    cJSON_AddItemToObject(SEND, "TYPE", TYPE);
    cJSON_AddItemToObject(SEND, "RESULT", RESULT);
    cJSON_AddItemToObject(SEND, "LOGIN", LOGIN);

    send_str = cJSON_Print(SEND);
    //send string-JSON to client
    write(user_sock, send_str, strlen(send_str));

    cJSON_Delete(SEND);
    free(send_str);
}