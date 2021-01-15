//
// Created by Igor Khanenko on 1/4/21.
//

#include "client.h"

extern t_client_st cl_listener;
//static void account_login_request(t_system *sys, t_user *user) {
//    char *str_user_json;
//
//    sys->registration = true;
//    if (malloc_size(user->login)) {
//        free(user->login);
//    }
//    if (malloc_size(user->password)) {
//        free(user->password);
//    }
//    str_user_json = mx_create_user_profile(sys, user);
//    write(sys->sockfd, str_user_json, strlen(str_user_json));
//    free(str_user_json);
//}

void mx_authentication_client(t_system *sys, t_user *user, cJSON *SERVER_JSON) {
    cJSON *RESULT = cJSON_GetObjectItemCaseSensitive(SERVER_JSON,
                                                     "RESULT");
    cJSON *MY_ID = cJSON_GetObjectItemCaseSensitive(SERVER_JSON,
                                                    "USER_ID");
    cJSON *CONTACTS = cJSON_GetObjectItemCaseSensitive(SERVER_JSON,
                                                       "CONTACTS_ID");
    cJSON *CHATS = cJSON_GetObjectItemCaseSensitive(SERVER_JSON,
                                                       "CHATS_ID");
    char *id = mx_itoa(MY_ID->valueint);
    //mx_printstr("mx_authentication_client\n");
    if (cJSON_IsFalse(RESULT)) {
        cl_listener.authentication = 2;
        if (MY_ID->valueint == 0) {
            write(1, "\nOops! This login doesn't exist.\n\n", 34);
            mx_account_login_request(sys, user);
        } else if (MY_ID->valueint == -1) {
            write(1, "\nOops! You entered an incorrect password. Please try again.\n\n", 61);
            mx_account_login_request(sys, user);
        }
    }
    else { //RESULT = TRUE (аутентификация прошла успеexitшно)
        write(1, "\nWell done! You successfully logged in to G-Chat.\nYour ID: ", 60);
        write(1, id, strlen(id));
        user->my_id = MY_ID->valueint;
//        user->contacts = cJSON_(SERVER_JSON
        sys->registration = true;
        sys->authentication = 1;
        sys->menu = true;
        cl_listener.authentication = true;
    }
    cJSON_DeleteItemFromObject(SERVER_JSON, "RESULT");
    cJSON_DeleteItemFromObject(SERVER_JSON, "USER_ID");
    free(id);
}
