//
// Created by mac on 15.01.2021.
//

#include "client.h"

extern t_client_st cl_listener;

void mx_found_users_by_substr(t_system *sys, t_user *user, t_json *json) {
//    mx_printstr("recieved results from server\n");
    json->RESULT = cJSON_GetObjectItemCaseSensitive(json->SERVER_JSON,
                                                    "RESULT");
    //Cleaning memory from previous searches
    if (sys->found_usernames != NULL) {
        for (int i = 0; i < sys->found_usernames_count; i++) {
            if (sys->found_usernames[i] != NULL) {
                free(sys->found_usernames[i]);
            }
        }
        free(sys->found_usernames);
        sys->found_usernames = NULL;
    }
    sys->found_usernames_count = 0;

    if (cJSON_IsFalse(json->RESULT)) {
        write (1, "LOGINS DON'T EXIST\n", 20); // это затычка!
        // здесь должна выводится пустая строка с сообщением, что пользователи не найдены
    }
    else { //RESULT = TRUE (user found successfully)
        json->FOUND_USERNAMES = cJSON_GetObjectItemCaseSensitive(json->SERVER_JSON,
                                                                 "FOUND_USERNAMES");
        sys->found_usernames_count = cJSON_GetArraySize(json->FOUND_USERNAMES);
        sys->found_usernames = (char **) malloc(sizeof(char *) * (sys->found_usernames_count + 1));
        for (int i = 0; i != sys->found_usernames_count; i++) {
            sys->found_usernames[i] = strdup(cJSON_GetArrayItem(json->FOUND_USERNAMES, i)->valuestring);
        }
        sys->found_usernames[sys->found_usernames_count] = NULL;
        // дальше нужно вывести эти логины пользователей в всплывающем окошке поиска
        
        cJSON_DeleteItemFromObject(json->SERVER_JSON, "FOUND_USERNAMES");
    }
    cJSON_DeleteItemFromObject(json->SERVER_JSON, "RESULT");
    cl_listener.awaiting_fs_res = false;
//    mx_printstr("users_found\n");
}
