//
// Created by Igor Khanenko on 1/4/21.
//

#include "client.h"

void user_chats_parse_and_save(t_user *user, t_json *json) {

}

void user_contacts_parse_and_save(t_user *user, t_json *json) {

}

void mx_authentication_client(t_system *sys, t_user *user, t_json *json) {
    json->RESULT = cJSON_GetObjectItemCaseSensitive(json->SERVER_JSON,
                                                     "RESULT");
    json->USER_ID = cJSON_GetObjectItemCaseSensitive(json->SERVER_JSON,
                                                    "USER_ID");
//    char *id = mx_itoa(MY_ID->valueint);

    if (cJSON_IsFalse(json->RESULT)) {
        sys->authentication = false;
        if (json->USER_ID->valueint == 0) { // login doesn't exist
            // нужно вывести сообщение о ошибке на экран
        }
        else if (json->USER_ID->valueint == -1) { // wrong password
            // нужно вывести сообщение о ошибке на экран
        }
    }
    else { //RESULT = TRUE (login and password are confirmed - successful LOG IN)
        user_contacts_parse_and_save(user, json);
        user_chats_parse_and_save(user, json);
//        user->contacts = cJSON_(SERVER_JSON
        sys->registration = true;
        sys->authentication = true;
        sys->menu = true;
    }
    cJSON_DeleteItemFromObject(SERVER_JSON, "RESULT");
    cJSON_DeleteItemFromObject(SERVER_JSON, "USER_ID");
    free(id);
}
