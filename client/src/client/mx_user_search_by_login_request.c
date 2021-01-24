//
// Created by mac on 24.01.2021.
//

#include "client.h"


void mx_user_search_by_login_request(t_system *sys, t_json *json) {
    char *send_str = NULL;

    json->SEND = cJSON_CreateObject();
    json->TYPE = cJSON_CreateNumber(USER_SEARCH_BY_LOGIN);
    json->LOGIN_SUBSTR = cJSON_CreateString(sys->searched_login);

    printf("SEARCHED_LOGIN = %s\n", json->SEARCHED_LOGIN->valuestring);

    cJSON_AddItemToObject(json->SEND, "TYPE", json->TYPE);
    cJSON_AddItemToObject(json->SEND, "SEARCHED_LOGIN", json->SEARCHED_LOGIN);

    send_str = cJSON_Print(json->SEND);

    write(sys->sockfd, send_str, strlen(send_str));
    cJSON_DeleteItemFromObject(json->SEND, "TYPE");
    cJSON_DeleteItemFromObject(json->SEND, "SEARCHED_LOGIN");

    cJSON_Delete(json->SEND);
    free(send_str);
}