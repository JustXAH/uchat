//
// Created by mac on 16.01.2021.
//

#include "client.h"

void mx_add_new_contact_request(t_system *sys, t_user * user, t_json *json, int index) {
    char *send_str = NULL;

    json->SERVER_JSON = cJSON_CreateObject();
    json->TYPE = cJSON_CreateNumber(NEW_CONTACT);

    json->USER_ID = cJSON_CreateNumber(user->my_id);
    json->CONTACT_ID = cJSON_CreateNumber(user->contacts_id[index]);

    cJSON_AddItemToObject(json->SERVER_JSON, "TYPE", json->TYPE);
    cJSON_AddItemToObject(json->SERVER_JSON, "USER_ID", json->USER_ID);
    cJSON_AddItemToObject(json->SERVER_JSON, "CONTACT_ID", json->CONTACT_ID);

    send_str = cJSON_Print(json->SERVER_JSON);

    write(sys->sockfd, send_str, strlen(send_str));
    
    free(send_str);
    cJSON_Delete(json->SERVER_JSON);
}