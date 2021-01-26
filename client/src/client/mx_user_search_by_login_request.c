//
// Created by mac on 24.01.2021.
//
#include "client.h"

extern t_client_st cl_listener;

void mx_user_search_by_login_request(t_system *sys, t_json *json) {
    mx_printstr("1\n");
    char *send_str = NULL;

    json->SEND = cJSON_CreateObject();
    mx_printstr("2\n");
    json->TYPE = cJSON_CreateNumber(USER_SEARCH_BY_LOGIN);
    mx_printstr("3\n");
    json->SEARCHED_LOGIN = cJSON_CreateString(sys->searched_login);

    printf("SEARCHED_LOGIN = %s\n", json->SEARCHED_LOGIN->valuestring);

    cJSON_AddItemToObject(json->SEND, "TYPE", json->TYPE);
    cJSON_AddItemToObject(json->SEND, "SEARCHED_LOGIN", json->SEARCHED_LOGIN);

    send_str = cJSON_Print(json->SEND);

    write(sys->sockfd, send_str, strlen(send_str));
    cJSON_DeleteItemFromObject(json->SEND, "TYPE");
    cJSON_DeleteItemFromObject(json->SEND, "SEARCHED_LOGIN");

    cJSON_Delete(json->SEND);
    free(send_str);
    cl_listener.pending_requests[USER_SEARCH_BY_LOGIN] = true;
}
