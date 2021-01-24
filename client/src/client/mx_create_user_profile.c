//
// Created by Igor Khanenko on 12/26/20.
//

#include "client.h"

static void registration_func(t_system  *sys, t_user **user) {
    char buff[24];

    if (sys->first_reg == true) {
        write(1, "Create your G-Chat account!\n", 28);
        write(1, "Please enter your username: ", 28);
        scanf("%s", buff);
        (*user)->login = strdup(buff);
        memset(buff, '\0', 20);
    }
    write(1, "Please enter your password: ", 28);
    scanf("%s", buff);
    (*user)->password = strdup(buff);
    memset(buff, '\0', 20);
    write(1, "Confirm your password: ", 23);
    scanf("%s", buff);
    if (strcmp((*user)->password, buff) != 0) {
        free((*user)->password);
        memset(buff, '\0', 20);
        registration_func(sys, user);
    }
}

static void log_in(t_user **user) {
    char buff[24];

    write(1, "Please enter your username and password\n", 40);
    write(1, "Login: ", 7);
    scanf("%s", buff);
    (*user)->login = strdup(buff);
    memset(buff, '\0', 20);
    write(1, "Password: ", 10);
    scanf("%s", buff);
    (*user)->password = strdup(buff);
    memset(buff, '\0', 20);
}

char *mx_create_user_profile(t_system *sys, t_user *user) {
    char *str_user = NULL;
    cJSON *USER = cJSON_CreateObject();
    cJSON *TYPE = NULL;
    cJSON *LOGIN = NULL;
    cJSON *PASS = NULL;

    if (sys->reg_confirmation == false) {
        registration_func(sys, &user);
        sys->reg_confirmation = true;
        TYPE = cJSON_CreateNumber(3);
    }
    else {
        log_in(&user);
        TYPE = cJSON_CreateNumber(2);
    }

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
    return str_user;
}
