//
// Created by mac on 11.01.2021.
//

#include "client.h"

void mx_registration_or_login_request(t_system *sys, t_user *user) {
    char *str_user = NULL;
    cJSON *USER = cJSON_CreateObject();
    cJSON *TYPE = NULL;
    cJSON *LOGIN = NULL;
    cJSON *PASS = NULL;

    TYPE = sys->registration == true ? cJSON_CreateNumber(3) : cJSON_CreateNumber(2);

    LOGIN = cJSON_CreateString(user->login);
    PASS = cJSON_CreateString(user->password);

    cJSON_AddItemToObject(USER, "TYPE", TYPE);
    cJSON_AddItemToObject(USER, "LOGIN", LOGIN);
    cJSON_AddItemToObject(USER, "PASS", PASS);

    str_user = cJSON_Print(USER);
//    write(1, str_js, strlen(str_js));
//    write(1, "\n", 1);
    cJSON_DeleteItemFromObject(USER, "TYPE");
    cJSON_DeleteItemFromObject(USER, "LOGIN");
    cJSON_DeleteItemFromObject(USER, "PASS");
    cJSON_Delete(USER);
    write(sys->sockfd, str_user, strlen(str_user));
    free(str_user);
}
