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
    printf(sys->reg_request == true ? "reg request sent\n" : "log request sent");
    TYPE = sys->reg_request == true ? cJSON_CreateNumber(REGISTRATION) : cJSON_CreateNumber(AUTHENTICATION);
    sys->reg_request = false;

    LOGIN = cJSON_CreateString(user->login);
    PASS = cJSON_CreateString(user->password);

//    printf("LOGIN = %s\nPASS = %s\n", user->login, user->password);
//    printf("LOGIN = %s\nPASS = %s\n", LOGIN->valuestring, PASS->valuestring);

    cJSON_AddItemToObject(USER, "TYPE", TYPE);
    cJSON_AddItemToObject(USER, "LOGIN", LOGIN);
    cJSON_AddItemToObject(USER, "PASS", PASS);

//    printf("LOGIN = %s\nPASS = %s\n", LOGIN->valuestring, json->PASS->valuestring);

    str_user = cJSON_Print(USER);
//    write(1, str_js, strlen(str_js));
//    write(1, "\n", 1);

    write(sys->sockfd, str_user, strlen(str_user));
    cJSON_DeleteItemFromObject(USER, "TYPE");
    cJSON_DeleteItemFromObject(USER, "LOGIN");
    cJSON_DeleteItemFromObject(USER, "PASS");
    cJSON_Delete(USER);
    free(str_user);
}
