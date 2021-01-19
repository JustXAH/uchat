//
// Created by Igor Khanenko on 1/4/21.
//

#include "client.h"

extern t_client_st cl_listener;

void user_chats_parse_and_save(t_user *user, t_json *json) {
    user->chats_count = cJSON_GetObjectItemCaseSensitive(json->SERVER_JSON,
                                                            "CHATS_COUNT")->valueint;
    json->CHATS_ID_ARR = cJSON_GetObjectItemCaseSensitive(json->SERVER_JSON,
                                                             "CHATS_ID_ARR");
    json->CHATS_NAME_ARR = cJSON_GetObjectItemCaseSensitive(json->SERVER_JSON,
                                                                "CHATS_NAME_ARR");

    if(user->chats_count != 0) {
        user->chats_id = (int *) malloc(sizeof(int) * user->chats_count);
        user->chats_name = (char **) malloc(sizeof(char *) * user->chats_count + 1);

        for (int i = 0; i != user->chats_count; i++) {
            user->chats_id[i] = cJSON_GetArrayItem(json->CHATS_ID_ARR, i)->valueint;
            user->chats_name[i] = strdup(cJSON_GetArrayItem(json->CHATS_NAME_ARR, i)->valuestring);
        }
        user->chats_name[user->contacts_count] = NULL;
    }
    cJSON_DeleteItemFromObject(json->SERVER_JSON, "CHATS_COUNT");
    cJSON_DeleteItemFromObject(json->SERVER_JSON, "CHATS_ID_ARR");
    cJSON_DeleteItemFromObject(json->SERVER_JSON, "CHATS_NAME_ARR");
}

void user_contacts_parse_and_save(t_user *user, t_json *json) {
    user->contacts_count = cJSON_GetObjectItemCaseSensitive(json->SERVER_JSON,
                                                            "CONTACTS_COUNT")->valueint;
    json->CONTACTS_ID_ARR = cJSON_GetObjectItemCaseSensitive(json->SERVER_JSON,
                                                     "CONTACTS_ID_ARR");
    json->CONTACTS_LOGIN_ARR = cJSON_GetObjectItemCaseSensitive(json->SERVER_JSON,
                                                     "CONTACTS_LOGIN_ARR");

    if(user->contacts_count != 0) {
        user->contacts_id = (int *) malloc(sizeof(int) * user->contacts_count);
        user->contacts_login = (char **) malloc(sizeof(char *) * user->contacts_count + 1);

        for (int i = 0; i != user->contacts_count; i++) {
            user->contacts_id[i] = cJSON_GetArrayItem(json->CONTACTS_LOGIN_ARR, i)->valueint;
            user->contacts_login[i] = strdup(cJSON_GetArrayItem(json->CONTACTS_LOGIN_ARR, i)->valuestring);
        }
        user->contacts_login[user->contacts_count] = NULL;
    }
    cJSON_DeleteItemFromObject(json->SERVER_JSON, "CONTACTS_COUNT");
    cJSON_DeleteItemFromObject(json->SERVER_JSON, "CONTACTS_ID_ARR");
    cJSON_DeleteItemFromObject(json->SERVER_JSON, "CONTACTS_LOGIN_ARR");
}

void mx_authentication_client(t_system *sys, t_user *user, t_json *json) {
    json->RESULT = cJSON_GetObjectItemCaseSensitive(json->SERVER_JSON,
                                                     "RESULT");
    json->USER_ID = cJSON_GetObjectItemCaseSensitive(json->SERVER_JSON,
                                                    "USER_ID");

    if (cJSON_IsFalse(json->RESULT)) {
        sys->authentication = false;
        if (json->USER_ID->valueint == 0) { // login doesn't exist
            write (1, "LOGIN DOESN'T EXIST\n", 20); // это затычка!
            // нужно вывести сообщение о ошибке на экран и запустить поторную процедуру логина
            cl_listener.authentication = 2;
        }
        else  { // "-1" wrong password
            write (1, "WRONG PASSWORD\n", 15); // это затычка!
            // нужно вывести сообщение о ошибке на экран и запустить поторную процедуру логина
            cl_listener.authentication = 2;
        }
    }
    else { //RESULT = TRUE (login and password are confirmed - successful LOG IN)
        user->my_id = json->USER_ID->valueint;
        //user_contacts_parse_and_save(user, json);
        //user_chats_parse_and_save(user, json);
//        user->contacts = cJSON_(SERVER_JSON
        sys->authentication = true;
        sys->menu = true;
        // вход в логин прошел успешно! дальше нужно перейти в окно МЕНЮ чата
        cl_listener.authentication = 1;
    }
    cJSON_DeleteItemFromObject(json->SERVER_JSON, "RESULT");
    cJSON_DeleteItemFromObject(json->SERVER_JSON, "USER_ID");
}
