//
// Created by Igor Khanenko on 1/4/21.
//

#include "client.h"

extern t_client_st cl_listener;

void user_voices_parse_and_save(t_user *user, t_json *json) {
    json->VOICES_ID_ARR = cJSON_GetObjectItemCaseSensitive(json->SERVER_JSON,
                                                           "VOICES_ID_ARR");
    json->VOICES_NAME_ARR = cJSON_GetObjectItemCaseSensitive(json->SERVER_JSON,
                                                             "VOICES_NAME_ARR");

    user->voices_id = (int *) malloc(sizeof(int) * NUMBER_VOICES);
    user->voices_name = (char **) malloc(sizeof(char *) * NUMBER_VOICES + 1);

    for (int i = 0; i != NUMBER_VOICES; i++) {
        if (json->VOICES_ID_ARR == NULL) {
            user->voices_id[i] = 0;
        }
        else {
            user->voices_id[i] = cJSON_GetArrayItem(json->VOICES_ID_ARR,
                                                    i)->valueint;
        }
        if (json->VOICES_NAME_ARR == NULL) {
            user->voices_name[i] = mx_strjoin("VOX ", mx_itoa(i + 1));
        }
        else if (cJSON_GetArrayItem(json->VOICES_NAME_ARR, i)->valuestring ==
                   NULL) {
            user->voices_name[i] = mx_strjoin("VOX ", mx_itoa(i + 1));
        }
        else {
            user->voices_name[i] = strdup(
                    cJSON_GetArrayItem(json->VOICES_NAME_ARR, i)->valuestring);
        }
        printf("\nuser->voices_name[%d] = |%s|\n", i, user->voices_name[i]);
    }
    user->voices_name[NUMBER_VOICES] = NULL;
}

void user_chats_parse_and_save(t_user *user, t_json *json) {
    user->chats_count = cJSON_GetObjectItemCaseSensitive(json->SERVER_JSON,
                                                            "CHATS_COUNT")->valueint;
    json->CHATS_ID_ARR = cJSON_GetObjectItemCaseSensitive(json->SERVER_JSON,
                                                             "CHATS_ID_ARR");
    json->CHATS_NAME_ARR = cJSON_GetObjectItemCaseSensitive(json->SERVER_JSON,
                                                                "CHATS_NAME_ARR");
    json->NOTIFICATION = cJSON_GetObjectItemCaseSensitive(json->SERVER_JSON, "NOTIFICATION");

    if(user->chats_count != 0) {
        user->chats_id = (int *) malloc(sizeof(int) * user->chats_count);
        user->chats_name = (char **) malloc(sizeof(char *) * user->chats_count + 1);
        user->notification = (int *) malloc(sizeof(int) * user->chats_count);

        for (int i = 0; i != user->chats_count; i++) {
            user->chats_id[i] = cJSON_GetArrayItem(json->CHATS_ID_ARR, i)->valueint;
            user->chats_name[i] = strdup(cJSON_GetArrayItem(json->CHATS_NAME_ARR, i)->valuestring);
            user->notification[i] = cJSON_GetArrayItem(json->NOTIFICATION, i)->valueint;
            printf("notification = %d\n", user->notification[i]);
        }
        user->chats_name[user->contacts_count] = NULL;
    }
//    cJSON_DeleteItemFromObject(json->SERVER_JSON, "CHATS_COUNT");
//    cJSON_DeleteItemFromObject(json->SERVER_JSON, "CHATS_ID_ARR");
//    cJSON_DeleteItemFromObject(json->SERVER_JSON, "CHATS_NAME_ARR");
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
            user->contacts_id[i] = cJSON_GetArrayItem(json->CONTACTS_ID_ARR, i)->valueint;
            user->contacts_login[i] = strdup(cJSON_GetArrayItem(json->CONTACTS_LOGIN_ARR, i)->valuestring);
        }
        user->contacts_login[user->contacts_count] = NULL;
    }
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
        user_contacts_parse_and_save(user, json);
        user_chats_parse_and_save(user, json);
        user_voices_parse_and_save(user, json);
//        user->contacts = cJSON_(SERVER_JSON
        sys->authentication = true;
        sys->menu = true;
        // вход в логин прошел успешно! дальше нужно перейти в окно МЕНЮ чата
        cl_listener.authentication = 1;
        cl_listener.my_id = json->USER_ID->valueint;
        
        for (int i = 0; i != user->contacts_count; i++) {
            mx_printstr("adding contact ");
            mx_printstr(user->contacts_login[i]);
            mx_printstr("\n");
            mb_contact_list_add(user->chats_id[i], user->contacts_id[i], user->contacts_login[i], false);
        }
    }
//    cJSON_DeleteItemFromObject(json->SERVER_JSON, "RESULT");
//    cJSON_DeleteItemFromObject(json->SERVER_JSON, "USER_ID");
//void user_take_vox_names(t_user *user, t_json *json) {
//
//    }
//    void gtk_menu_item_set_label (GtkMenuItem *menu_item, const gchar *label);
}
