//
// Created by Igor Khanenko on 12/26/20.
//

#include "client.h"

char *mx_create_user_profile(t_client *cli) {
    char *str_user = NULL;
    cJSON *USER = cJSON_CreateObject();
    cJSON *TYPE = cJSON_CreateNumber(2);
    cJSON *LOGIN = cJSON_CreateString(cli->login);
    cJSON *PASS = cJSON_CreateString(cli->password);


    cJSON_AddItemToObject(USER, "TYPE", TYPE);
    cJSON_AddItemToObject(USER, "LOGIN", LOGIN);
    cJSON_AddItemToObject(USER, "PASS", PASS);

    str_user = cJSON_Print(USER);
//    write(1, str_js, strlen(str_js));
//    write(1, "\n", 1);
    cJSON_Delete(USER);
    return str_user;
}
