//
// Created by mac on 09.01.2021.
//

#include "server.h"

void mx_user_search_by_login(t_server *serv, t_json *json, int user_sock) {
    char *send_str = NULL;
    t_user_info *user = NULL;

    json->SEND = cJSON_CreateObject();
    json->TYPE = cJSON_CreateNumber(USER_SEARCH_BY_LOGIN);
    json->SEARCHED_LOGIN = cJSON_GetObjectItemCaseSensitive(json->USER_JSON, "SEARCHED_LOGIN");

    json->FOUND_USER_ID = cJSON_CreateNumber(mx_db_check_login_exist(serv->db, json->SEARCHED_LOGIN->valuestring));
    if (json->USER_ID->valueint == 0) { // "0" - login doesn't exist
        json->RESULT = cJSON_CreateFalse();
    }
    else {
        json->RESULT = cJSON_CreateTrue(); //логин найден успешно
        user = mx_db_get_user(serv->db, json->FOUND_USER_ID->valueint);
        json->FOUND_LOGIN = cJSON_CreateString(user->login);
    }
    cJSON_AddItemToObject(json->SEND, "TYPE", json->TYPE);
    cJSON_AddItemToObject(json->SEND, "RESULT", json->RESULT);
    cJSON_AddItemToObject(json->SEND, "FOUND_USER_ID", json->FOUND_USER_ID);
    cJSON_AddItemToObject(json->SEND, "FOUND_LOGIN", json->FOUND_LOGIN);

    send_str = cJSON_Print(json->SEND);

    write(user_sock, send_str, strlen(send_str));

    cJSON_Delete(json->SEND);
    free(send_str);
}
