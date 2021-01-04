//
// Created by Igor Khanenko on 12/26/20.
//

#include "client.h"

static void authentication(t_client *cli) {
    char buff[20];

    write(1, "Please enter your username and password\n", 40);
    write(1, "Login: ", 7);
    scanf("%s", buff);
    cli->login = strdup(buff);
    memset(buff, '\0', 20);
    write(1, "Password: ", 10);
    scanf("%s", buff);
    cli->password = strdup(buff);
    memset(buff, '\0', 20);
//    write(1, "\nPlease enter your nickname: ", 29);
//    scanf("%s", buff);
//    cli->nick = strdup(buff);
//    memset(buff, '\0', 20);
//    write(1, "\nPlease enter your birthday: ", 29);
//    scanf("%s", buff);
//    cli->birth = strdup(buff);
//    memset(buff, '\0', 20);
}

char *mx_create_user_profile(t_client *cli) {
    char *str_user = NULL;
    cJSON *USER = cJSON_CreateObject();
    cJSON *TYPE = cJSON_CreateNumber(2);
    cJSON *LOGIN = NULL;
    cJSON *PASS = NULL;

    authentication(cli);

    LOGIN = cJSON_CreateString(cli->login);
    PASS = cJSON_CreateString(cli->password);

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
    return str_user;
}
