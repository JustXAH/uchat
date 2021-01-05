//
// Created by Igor Khanenko on 1/5/21.
//

#include "client.h"

void mx_confirmation_of_registration(cJSON *SERVER_JSON, t_client *cli) {
    char *str_user_json;
    cJSON *RESULT = NULL;
    bool registration = true;
//    cJSON *MESSAGE = NULL;

    RESULT = cJSON_GetObjectItemCaseSensitive(SERVER_JSON,
                                              "RESULT");
//    MESSAGE = cJSON_GetObjectItemCaseSensitive(SERVER_JSON,
//                                               "MESSAGE");
//    printf("\n%s", MESSAGE->valuestring);
    if (cJSON_IsFalse(RESULT)) { //ошибка при регистрации
        write(1, "\nWhoops! Such an account already exists. Please try another username.\n\n", 73);
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
    else { //RESULT = TRUE (регистрация прошла успешно)
        write(1, "\nCongratulations on your successful G-Chat account registration!", 63);
        cli->registration = true;
        cli->authentication = true;
    }
    cJSON_DeleteItemFromObject(SERVER_JSON, "RESULT");
}
