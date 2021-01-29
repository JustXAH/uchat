//
// Created by Igor Khanenko on 15.01.2021.
//

#include "client.h"

void mx_found_users_by_substr(t_system *sys, t_user *user, t_json *json) {

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

    if (cJSON_IsTrue(json->RESULT)) {
        json->FOUND_USERNAMES = cJSON_GetObjectItemCaseSensitive(json->SERVER_JSON,
                                                                 "FOUND_USERNAMES");
        sys->found_usernames_count = cJSON_GetArraySize(json->FOUND_USERNAMES);
        sys->found_usernames = (char **) malloc(sizeof(char *) * (sys->found_usernames_count + 1));
        for (int i = 0; i != sys->found_usernames_count; i++) {
            sys->found_usernames[i] = strdup(cJSON_GetArrayItem(json->FOUND_USERNAMES, i)->valuestring);
        }
        sys->found_usernames[sys->found_usernames_count] = NULL;
    }
}
