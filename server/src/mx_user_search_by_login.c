//
// Created by mac on 09.01.2021.
//

#include "server.h"

void mx_user_search_by_login(t_server *serv, t_json *json, int user_index) {
    char *send_str = NULL;
    t_user_info *user = NULL;
    mx_printstr("mx_user_search_by_login started\n");
    json->SEND = cJSON_CreateObject();
    json->TYPE = cJSON_CreateNumber(USER_SEARCH_BY_LOGIN);
    json->SEARCHED_LOGIN = cJSON_GetObjectItemCaseSensitive(json->USER_JSON, "SEARCHED_LOGIN");
    mx_printstr("mx_user_search_by_login 1\n");
    json->FOUND_USER_ID = cJSON_CreateNumber(mx_db_check_login_exist(serv->db, json->SEARCHED_LOGIN->valuestring));
    if (json->FOUND_USER_ID->valueint == 0) { // "0" - login doesn't exist
        json->RESULT = cJSON_CreateFalse();
    }
    else {
        json->RESULT = cJSON_CreateTrue(); //логин найден успешно
        mx_printstr("mx_user_search_by_login 2\n");
        user = mx_db_get_user(serv->db, json->FOUND_USER_ID->valueint);
        mx_printstr("mx_user_search_by_login 3\n");
        json->FOUND_LOGIN = cJSON_CreateString(user->login);
    }
    cJSON_AddItemToObject(json->SEND, "TYPE", json->TYPE);
    cJSON_AddItemToObject(json->SEND, "RESULT", json->RESULT);
    cJSON_AddItemToObject(json->SEND, "FOUND_USER_ID", json->FOUND_USER_ID);
    cJSON_AddItemToObject(json->SEND, "FOUND_LOGIN", json->FOUND_LOGIN);

    send_str = cJSON_Print(json->SEND);
    mx_printstr(send_str);
    write(serv->user_socket[user_index], send_str, strlen(send_str));

    cJSON_Delete(json->SEND);
    free(send_str);
    mx_printstr("mx_suer_search_by_login finished\n");
}
