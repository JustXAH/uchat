//
// Created by Igor Khanenko on 1/5/21.
//

#include "client.h"

static void registration_request(t_client *cli ) {
    char *str_user_json;
    bool registration = true;

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

void mx_confirmation_of_registration(cJSON *SERVER_JSON, t_client *cli) {
    cJSON *RESULT = cJSON_GetObjectItemCaseSensitive(SERVER_JSON,
                                                     "RESULT");
    cJSON *MY_ID = cJSON_GetObjectItemCaseSensitive(SERVER_JSON,
                                                    "USER_ID");
    char *id = mx_itoa(MY_ID->valueint);

    if (cJSON_IsFalse(RESULT)) { // ошибка при регистрации
        write(1, "\nWhoops! Such an account already exists. Please try another username.\n\n", 73);
        registration_request(cli);
    }
    else { // RESULT = TRUE (регистрация прошла успешно)
        write(1, "\nCongratulations on your successful G-Chat account registration!\nYour ID: ", 74);
        write(1, id, strlen(id));
        cli->registration = true;
        cli->authentication = true;
        cli->my_id = MY_ID->valueint;
    }
    cJSON_DeleteItemFromObject(SERVER_JSON, "RESULT");
    cJSON_DeleteItemFromObject(SERVER_JSON, "USER_ID");
//    cJSON_Delete(RESULT);
//    cJSON_Delete(MY_ID);
    free(id);
}
