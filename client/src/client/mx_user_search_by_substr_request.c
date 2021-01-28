//
// Created by mac on 24.01.2021.
//
#include "client.h"

extern t_client_st cl_listener;

void mx_user_search_by_substr_request(t_system *sys, t_json *json) {
    char *send_str = NULL;

    json->SEND = cJSON_CreateObject();
    json->TYPE = cJSON_CreateNumber(USER_SEARCH_BY_SUBSTRING);
    json->LOGIN_SUBSTR = cJSON_CreateString(sys->login_substr);

    printf("LOGIN_SUBSTR = %s\n", json->LOGIN_SUBSTR->valuestring);

    cJSON_AddItemToObject(json->SEND, "TYPE", json->TYPE);
    cJSON_AddItemToObject(json->SEND, "LOGIN_SUBSTR", json->LOGIN_SUBSTR);

    send_str = cJSON_Print(json->SEND);
    write(sys->sockfd, send_str, strlen(send_str));
    printf("Search by substr request sent\n");

    cJSON_Delete(json->SEND);
    free(send_str);
    cl_listener.pending_requests[USER_SEARCH_BY_SUBSTRING] = true;
}
