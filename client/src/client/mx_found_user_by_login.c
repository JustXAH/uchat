//
// Created by mac on 15.01.2021.
//

#include "client.h"

void mx_found_user_by_login(t_system *sys, t_user *user, t_json *json) {
    char *file_path = NULL;

    json->RESULT = cJSON_GetObjectItemCaseSensitive(json->SERVER_JSON,
                                                    "RESULT");
    if (MALLOC_SIZE(sys->found_user_login)) {
        mx_strdel(&sys->found_user_login);
    }
    if (cJSON_IsFalse(json->RESULT)) {
        sys->found_user_login = NULL;
        sys->found_user_id = -1;
    }
    else { //RESULT = TRUE (user found successfully)
        json->FOUND_USER_ID = cJSON_GetObjectItemCaseSensitive(json->SERVER_JSON,
                                                               "FOUND_USER_ID");
        json->FOUND_LOGIN = cJSON_GetObjectItemCaseSensitive(json->SERVER_JSON,
                                                             "FOUND_LOGIN");
        json->DISPATCH = cJSON_GetObjectItemCaseSensitive(json->SERVER_JSON,
                                                          "DISPATCH");

        sys->found_user_id = json->FOUND_USER_ID->valueint;
        sys->found_user_login = mx_strdup(json->FOUND_LOGIN->valuestring);

        if (cJSON_IsTrue(json->DISPATCH)) {
            json->FILENAME = cJSON_GetObjectItemCaseSensitive(json->SERVER_JSON,
                                                              "FILENAME");
            json->FILE_SIZE = cJSON_GetObjectItemCaseSensitive(json->SERVER_JSON,
                                                              "FILE_SIZE");
            if (MALLOC_SIZE(sys->filename)) {
                mx_strdel(&sys->filename);
            }
            sys->filename = strdup(json->FILENAME->valuestring);
            printf("You have been sent a user pic. User pic receiving...\n");
            file_path = mx_file_receiving(sys, sys->filename, json->FILE_SIZE->valueint);
            printf("Successfully received and save user pic from USER!\n");

            // при выходе из профайла удаление аватарки из кэша
            if (remove(file_path) == 0) {
                printf("Successfully removed user_pic from cache directory\n");
            }
            else {
                printf("ERROR while deleting user_pic!\n");
            }
        }
    }
    free(file_path);
}
