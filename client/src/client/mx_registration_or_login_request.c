//
// Created by mac on 11.01.2021.
//

#include "client.h"

void mx_registration_or_login_request(t_system *sys, t_user *user, t_json *json) {
    char *str_user = NULL;
    json->SEND = cJSON_CreateObject();
    printf(sys->reg_request == true ? "Registration request sent\n" : "Login request sent\n");
    json->TYPE = sys->reg_request == true ? cJSON_CreateNumber(REGISTRATION) : cJSON_CreateNumber(AUTHENTICATION);
    sys->reg_request = false;

    json->LOGIN = cJSON_CreateString(user->login);
//    json->PASS = cJSON_CreateString(user->password);
    json->PASS = cJSON_CreateString(user->hash_password);

    printf("LOGIN = %s\nPASS = %s\n", json->LOGIN->valuestring, json->PASS->valuestring);

    cJSON_AddItemToObject(json->SEND, "TYPE", json->TYPE);
    cJSON_AddItemToObject(json->SEND, "LOGIN", json->LOGIN);
    cJSON_AddItemToObject(json->SEND, "PASS", json->PASS);

    str_user = cJSON_Print(json->SEND);

    write(sys->sockfd, str_user, strlen(str_user));
    cJSON_DeleteItemFromObject(json->SEND, "TYPE");
    cJSON_DeleteItemFromObject(json->SEND, "LOGIN");
    cJSON_DeleteItemFromObject(json->SEND, "PASS");

    cJSON_Delete(json->SEND);
    free(str_user);
}
