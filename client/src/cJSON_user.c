//
// Created by Igor Khanenko on 12/26/20.
//

#include "client.h"

char *mx_create_json_profile(t_client *cli) {
    cJSON *send = cJSON_CreateObject();
    cJSON *LOGIN = cJSON_CreateString(cli->login);
    cJSON *PASS = cJSON_CreateString(cli->password);
    cJSON *NICK = cJSON_CreateString(cli->nick);
    cJSON *BIRTH = cJSON_CreateString(cli->birth);
    char *str_js = NULL;

    cJSON_AddItemToObject(send, "LOGIN", LOGIN);
    cJSON_AddItemToObject(send, "PASS", PASS);
    cJSON_AddItemToObject(send, "NICK", NICK);
    cJSON_AddItemToObject(send, "BIRTH", BIRTH);
    str_js = cJSON_Print(send);
    write(1, str_js, strlen(str_js));
//    write(1, "\n", 1);
    cJSON_Delete(send);
    return str_js;
}
