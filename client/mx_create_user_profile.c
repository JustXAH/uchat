//
// Created by Igor Khanenko on 12/26/20.
//

#include "client.h"

static void registration_func(t_client **cli) {
    char buff[24];

    if ((*cli)->first_reg == true) {
        write(1, "Create your G-Chat account!\n", 28);
        write(1, "Please enter your username: ", 28);
        scanf("%s", buff);
        (*cli)->login = strdup(buff);
        memset(buff, '\0', 20);
    }
    write(1, "Please enter your password: ", 28);
    scanf("%s", buff);
    (*cli)->password = strdup(buff);
    memset(buff, '\0', 20);
    write(1, "Confirm your password: ", 23);
    scanf("%s", buff);
    if (strcmp((*cli)->password, buff) != 0) {
        free((*cli)->password);
        memset(buff, '\0', 20);
        registration_func(cli);
    }
}

static void log_in(t_client *cli) {
    char buff[24];

    write(1, "Please enter your username and password\n", 40);
    write(1, "Login: ", 7);
    scanf("%s", buff);
    cli->login = strdup(buff);
    memset(buff, '\0', 20);
    write(1, "Password: ", 10);
    scanf("%s", buff);
    cli->password = strdup(buff);
    memset(buff, '\0', 20);
}

char *mx_create_user_profile(t_client *cli, bool registration) {
    char *str_user = NULL;
    cJSON *USER = cJSON_CreateObject();
    cJSON *TYPE = NULL;
    cJSON *LOGIN = NULL;
    cJSON *PASS = NULL;

    if (registration == true) {
        registration_func(&cli);
        registration = false;
        TYPE = cJSON_CreateNumber(3);
    }
    else {
        log_in(cli);
        TYPE = cJSON_CreateNumber(2);
    }

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
