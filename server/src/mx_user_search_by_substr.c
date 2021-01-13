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

void mx_user_search_by_substr(t_server *serv, char *u_login, int user_sock) {
    cJSON *SEND = cJSON_CreateObject();
    cJSON *TYPE = cJSON_CreateNumber(USER_SEARCH_BY_SUBSTRING);
    cJSON *RESULT = NULL; //результат аутентификации: FALSE - неудачно, TRUE - успешно
    cJSON *LOGINS_ARR = NULL;
    char **buff_arr;
    char *send_str = NULL;

   buff_arr = mx_db_search_logins_by_substr(serv->db, u_login);
    if (buff_arr == NULL) { // "NULL" - no login matches
        RESULT = cJSON_CreateFalse();
    }
    else {
        RESULT = cJSON_CreateTrue(); // there are logins matches by substring
        LOGINS_ARR = logins_arr_json_creator((const char **)buff_arr);
    }

    cJSON_AddItemToObject(SEND, "TYPE", TYPE);
    cJSON_AddItemToObject(SEND, "RESULT", RESULT);
    cJSON_AddItemToObject(SEND, "LOGINS_ARR", LOGINS_ARR);

    send_str = cJSON_Print(SEND);

    write(user_sock, send_str, strlen(send_str));

    cJSON_Delete(SEND);
    free(send_str);
    free(buff_arr);
}