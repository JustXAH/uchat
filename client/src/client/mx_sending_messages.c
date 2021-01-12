//
// Created by mac on 08.01.2021.
//

#include "client.h"

void mx_sending_messages(t_system *sys, t_user *user, char *buff) {
    char **split_str;
    char *str_send;
    cJSON *SEND = cJSON_CreateObject();
    cJSON *TYPE = cJSON_CreateNumber(1);
    cJSON *LOGIN = cJSON_CreateString(user->login);
    cJSON *TO = NULL;
    cJSON *MESSAGE = NULL;

    split_str = mx_strsplit(buff, ';');
    if (split_str[1] == NULL) {
        write(1,
              "\nERROR, invalid  struct of message.\nusage: [message][;][socket]",
              64);
        cJSON_Delete(TYPE);
        cJSON_Delete(LOGIN);
    }
    else {
        mx_del_char(split_str[1], mx_strlen(split_str[1]) - 1,
                    '\n');
        MESSAGE = cJSON_CreateString(split_str[0]);
        TO = cJSON_CreateNumber(mx_atoi(split_str[1]));
        cJSON_AddItemToObject(SEND, "TYPE", TYPE);
        cJSON_AddItemToObject(SEND, "LOGIN", LOGIN);
        cJSON_AddItemToObject(SEND, "MESSAGE", MESSAGE);
        cJSON_AddItemToObject(SEND, "TO", TO);
        str_send = cJSON_Print(SEND);
//                printf("\n\nJSON send to server:%s\n\n", str_send);
        write(sys->sockfd, str_send, strlen(str_send));
        if (malloc_size(str_send))
            free(str_send);
    }
    if (malloc_size(split_str))
        mx_del_strarr(&split_str);
    cJSON_Delete(SEND);
}
