//
// Created by mac on 24.01.2021.
//

#include "client.h"

extern t_client_st cl_listener;

void mx_add_new_chat_request(t_system *sys, t_user * user, t_json *json, int contact_id) {
    char *send_str = NULL;

    json->SERVER_JSON = cJSON_CreateObject();
    json->TYPE = cJSON_CreateNumber(NEW_CHAT);

    json->USER_ID = cJSON_CreateNumber(user->my_id);
    json->CONTACT_ID = cJSON_CreateNumber(contact_id);

    cJSON_AddItemToObject(json->SERVER_JSON, "TYPE", json->TYPE);
    cJSON_AddItemToObject(json->SERVER_JSON, "USER_ID", json->USER_ID);
    cJSON_AddItemToObject(json->SERVER_JSON, "CONTACT_ID", json->CONTACT_ID);

    send_str = cJSON_Print(json->SERVER_JSON);

    write(sys->sockfd, send_str, strlen(send_str));
    mx_printstr(send_str);
    free(send_str);
    cJSON_Delete(json->SERVER_JSON);
    cl_listener.pending_requests[NEW_CHAT] = true;
}
