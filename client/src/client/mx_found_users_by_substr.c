//
// Created by mac on 15.01.2021.
//

#include "client.h"

void mx_found_users_by_substr(t_system *sys, t_user *user, t_json *json) {
    json->RESULT = cJSON_GetObjectItemCaseSensitive(json->SERVER_JSON,
                                                    "RESULT");
    if (cJSON_IsFalse(json->RESULT)) {
        write (1, "LOGINS DON'T EXIST\n", 20); // это затычка!
        // здесь должна выводится пустая строка с сообщением, что пользователи не найдены
    }
    else { //RESULT = TRUE (user found successfully)
        json->FOUND_USERNAMES = cJSON_GetObjectItemCaseSensitive(json->SERVER_JSON,
                                                                 "FOUND_USERNAMES");
        sys->found_usernames_count = cJSON_GetArraySize(json->FOUND_USERNAMES);
        sys->found_usernames = (char **) malloc(sizeof(char *) * sys->found_usernames_count);

        for (int i = 0; i != sys->found_usernames_count; i++) {
            sys->found_usernames[i] = strdup(cJSON_GetArrayItem(json->FOUND_USERNAMES, i)->valuestring);
        }
        sys->found_usernames[sys->found_usernames_count] = NULL;

        // дальше нужно вывести эти логины пользователей в всплывающем окошке поиска

        cJSON_DeleteItemFromObject(json->SERVER_JSON, "FOUND_USERNAMES");
    }
    cJSON_DeleteItemFromObject(json->SERVER_JSON, "RESULT");
}
