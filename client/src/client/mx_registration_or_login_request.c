//
// Created by mac on 11.01.2021.
//

#include "client.h"

void mx_registration_or_login_request(t_system *sys, t_user *user, t_json *json) {
    char *str_user = NULL;
    json->SEND = cJSON_CreateObject();
    printf(sys->reg_request == true ? "reg request sent\n" : "log request sent\n");
    json->TYPE = sys->reg_request == true ? cJSON_CreateNumber(REGISTRATION) : cJSON_CreateNumber(AUTHENTICATION);
    sys->reg_request = false;

    json->LOGIN = cJSON_CreateString(user->login);
    json->PASS = cJSON_CreateString(user->password);

//    printf("LOGIN = %s\nPASS = %s\n", user->login, user->password);
    printf("LOGIN = %s\nPASS = %s\n", json->LOGIN->valuestring, json->PASS->valuestring);

    cJSON_AddItemToObject(json->SEND, "TYPE", json->TYPE);
    cJSON_AddItemToObject(json->SEND, "LOGIN", json->LOGIN);
    cJSON_AddItemToObject(json->SEND, "PASS", json->PASS);

//    printf("LOGIN = %s\nPASS = %s\n", LOGIN->valuestring, json->PASS->valuestring);
    str_user = cJSON_Print(json->SEND);
//    write(1, str_js, strlen(str_js));
//    write(1, "\n", 1);

    write(sys->sockfd, str_user, strlen(str_user));
    cJSON_DeleteItemFromObject(json->SEND, "TYPE");
    cJSON_DeleteItemFromObject(json->SEND, "LOGIN");
    cJSON_DeleteItemFromObject(json->SEND, "PASS");
    //mx_printstr("starting to free shit\n");
    cJSON_Delete(json->SEND);
    free(str_user);
    //mx_printstr("shit freed successfully\n");
}
