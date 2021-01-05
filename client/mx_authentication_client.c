//
// Created by Igor Khanenko on 1/4/21.
//

#include "client.h"

void mx_authentication_client(cJSON *SERVER_JSON, t_client *cli) {
    char *str_user_json;
    cJSON *RESULT = NULL;
    bool registration = false;
//    cJSON *MESSAGE = NULL;

    RESULT = cJSON_GetObjectItemCaseSensitive(SERVER_JSON,
                                              "RESULT");
//    MESSAGE = cJSON_GetObjectItemCaseSensitive(SERVER_JSON,
//                                               "MESSAGE");
//    printf("\n%s", MESSAGE->valuestring);
    if (cJSON_IsFalse(RESULT)) {
        write(1, "\nWhoops! Your login or password is incorrect!\n\n", 47);
        if (malloc_size(cli->login)) {
            free(cli->login);
        }
        if (malloc_size(cli->password)) {
            free(cli->password);
        }
        str_user_json = mx_create_user_profile(cli, registration);
        write(cli->sockfd, str_user_json, strlen(str_user_json));
        free(str_user_json);
    }
    else { //RESULT = TRUE (аутентификация прошла успеexitшно)
        write(1, "\nWell done! You successfully logged in to G-CHAT.", 49);
        cli->authentication = true;
    }
    cJSON_DeleteItemFromObject(SERVER_JSON, "RESULT");
}
