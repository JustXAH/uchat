//
// Created by mac on 12.01.2021.
//

#include "server.h"

void mx_get_login(t_server *serv, t_json *json, int user_index) {
    char *send_str = NULL;

    json->SEND = cJSON_CreateObject();
    json->TYPE = cJSON_CreateNumber(GET_LOGIN);

    json->FOUND_LOGIN = cJSON_CreateString(mx_db_get_login(serv->db, json->USER_ID->valueint));
    if (json->FOUND_LOGIN->valuestring == NULL) {
        json->RESULT = cJSON_CreateFalse(); // ошибка при регистрации - логин уже существует
    }
    else {
        json->RESULT = cJSON_CreateTrue(); //регистрация прошла успешно
    }
    cJSON_AddItemToObject(json->SEND, "TYPE", json->TYPE);
    cJSON_AddItemToObject(json->SEND, "RESULT", json->RESULT);
    cJSON_AddItemToObject(json->SEND, "FOUND_LOGIN", json->FOUND_LOGIN);

    send_str = cJSON_Print(json->SEND);
    //send string-JSON to client
    write(serv->user_socket[user_index], send_str, strlen(send_str));

    cJSON_Delete(json->SEND);
    free(send_str);
}
