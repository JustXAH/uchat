//
// Created by Igor Khanenko on 1/4/21.
//

#include "client.h"

static void account_login_request(t_client *cli ) {
    char *str_user_json;
    bool registration = false;

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

void mx_authentication_client(cJSON *SERVER_JSON, t_client *cli) {
    cJSON *RESULT = cJSON_GetObjectItemCaseSensitive(SERVER_JSON,
                                                     "RESULT");
    cJSON *MY_ID = cJSON_GetObjectItemCaseSensitive(SERVER_JSON,
                                                    "USER_ID");
    char *id = mx_itoa(MY_ID->valueint);

    if (cJSON_IsFalse(RESULT)) {
        if (MY_ID->valueint == 0) {
            write(1, "\nOops! This login doesn't exist.\n\n", 34);
            account_login_request(cli);
        } else if (MY_ID->valueint == -1) {
            write(1, "\nOops! You entered an incorrect password. Please try again.\n\n", 61);
            account_login_request(cli);
        }
    } else { //RESULT = TRUE (аутентификация прошла успеexitшно)
        write(1, "\nWell done! You successfully logged in to G-Chat.\nYour ID: ", 60);
        write(1, id, strlen(id));
        cli->my_id = MY_ID->valueint;
        cli->authentication = true;
    }
    cJSON_DeleteItemFromObject(SERVER_JSON, "RESULT");
    cJSON_DeleteItemFromObject(SERVER_JSON, "USER_ID");
//    cJSON_Delete(RESULT);
//    cJSON_Delete(MY_ID);
    free(id);
}
