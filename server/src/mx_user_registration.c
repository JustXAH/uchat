//
// Created by Igor Khanenko on 1/5/21.
//

#include "server.h"

void mx_user_registration(t_server *serv, t_json *json, int user_index) {
    char *send_str = NULL;

    json->LOGIN = cJSON_GetObjectItemCaseSensitive(json->USER_JSON, "LOGIN");
    json->PASS = cJSON_GetObjectItemCaseSensitive(json->USER_JSON, "PASS");
    json->SEND = cJSON_CreateObject();
    json->TYPE = cJSON_CreateNumber(REGISTRATION);

    json->USER_ID = cJSON_CreateNumber(mx_db_insert_new_user(serv->db, json->LOGIN->valuestring, json->PASS->valuestring));
    if (json->USER_ID->valueint == 0) { // "0" - ошибка при регистрации, логин уже существует
        json->RESULT = cJSON_CreateFalse();
    }
    else {
        json->RESULT = cJSON_CreateTrue(); //регистрация прошла успешно
    }
    cJSON_AddItemToObject(json->SEND, "TYPE", json->TYPE);
    cJSON_AddItemToObject(json->SEND, "RESULT", json->RESULT);
    cJSON_AddItemToObject(json->SEND, "USER_ID", json->USER_ID);

    send_str = cJSON_Print(json->SEND);
    //send string-JSON to client
    write(serv->user_socket[user_index], send_str, strlen(send_str));

    cJSON_Delete(json->SEND);
    free(send_str);
}
