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

void mx_user_search_by_substr(t_server *serv, t_json *json, int user_index) {
    char **buff_arr = NULL;
    char *send_str = NULL;

    json->SEND = cJSON_CreateObject();
    json->TYPE = cJSON_CreateNumber(USER_SEARCH_BY_SUBSTRING);
    json->LOGIN = cJSON_GetObjectItemCaseSensitive(json->USER_JSON, "LOGIN_SUBSTR");

    buff_arr = mx_db_search_logins_by_substr(serv->db, json->LOGIN->valuestring);
    if (buff_arr == NULL) { // "NULL" - no login matches
        json->RESULT = cJSON_CreateFalse();
    }
    else {
        json->RESULT = cJSON_CreateTrue(); // there are logins matches by substring
        json->FOUND_USERNAMES = logins_arr_json_creator((const char * const *)buff_arr);
    }
    cJSON_AddItemToObject(json->SEND, "TYPE", json->TYPE);
    cJSON_AddItemToObject(json->SEND, "RESULT", json->RESULT);
    cJSON_AddItemToObject(json->SEND, "FOUND_USERNAMES", json->FOUND_USERNAMES);

    send_str = cJSON_Print(json->SEND);

    write(serv->user_socket[user_index], send_str, strlen(send_str));

    cJSON_Delete(json->SEND);
    free(send_str);
    if (MALLOC_SIZE(buff_arr)) {
        mx_del_strarr(&buff_arr);
    }
}
