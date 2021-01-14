//
// Created by Igor Khanenko on 12.01.2021.
//

#include "server.h"

static cJSON *logins_arr_json_creator(const char * const *logins) {
    cJSON *LOGINS_ARR = NULL;
    int arr_len = 0;

    if (logins) {
        while (logins[arr_len] != NULL) {
            arr_len++;
        }
    }
    LOGINS_ARR = cJSON_CreateStringArray(logins, arr_len);

    return LOGINS_ARR;
}

void mx_user_search_by_substr(t_server *serv, t_json *json, int user_sock) {
    char **buff_arr = NULL;
    char *send_str = NULL;

    json->SEND = cJSON_CreateObject();
    json->TYPE = cJSON_CreateNumber(USER_SEARCH_BY_SUBSTRING);

    buff_arr = mx_db_search_logins_by_substr(serv->db, json->LOGIN->valuestring);
    if (buff_arr == NULL) { // "NULL" - no login matches
        json->RESULT = cJSON_CreateFalse();
    }
    else {
        json->RESULT = cJSON_CreateTrue(); // there are logins matches by substring
        json->USERS_LOGIN_ARR = logins_arr_json_creator((const char * const *)buff_arr);
    }
    cJSON_AddItemToObject(json->SEND, "TYPE", json->TYPE);
    cJSON_AddItemToObject(json->SEND, "RESULT", json->RESULT);
    cJSON_AddItemToObject(json->SEND, "USERS_LOGIN_ARR", json->USERS_LOGIN_ARR);

    send_str = cJSON_Print(json->SEND);

    write(user_sock, send_str, strlen(send_str));

    cJSON_Delete(json->SEND);
    free(send_str);
    if (MALLOC_SIZE(buff_arr)) {
        mx_del_strarr(&buff_arr);
    }
}
