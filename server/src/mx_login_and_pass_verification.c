//
// Created by Igor Khanenko on 1/2/21.
//

#include "server.h"

//static int int_arr_len(const int *arr) {
//    int len = 0;
//
//    while (arr[len] != 0) {
//        len++;
//    }
//    return len;
//}

void chats_json_creator(sqlite3 *db, t_json **json, int user) {
    t_chat *chats = mx_db_get_chats_info(db, user);

    (*json)->CHATS_ID_ARR = cJSON_CreateIntArray(chats->id, chats->count);
    (*json)->CHATS_NAME_ARR = cJSON_CreateStringArray((const char * const *)chats->chat_name, chats->count);
    (*json)->CHATS_COUNT = cJSON_CreateNumber(chats->count);

    cJSON_AddItemToObject((*json)->SEND, "CHATS_ID_ARR", (*json)->CHATS_ID_ARR);
    cJSON_AddItemToObject((*json)->SEND, "CHATS_NAME_ARR", (*json)->CHATS_NAME_ARR);
    cJSON_AddItemToObject((*json)->SEND, "CHATS_COUNT", (*json)->CHATS_COUNT);

    if (chats->count > 0) {
        if (MALLOC_SIZE(chats->id)) {
            free(chats->id);
        }
        if (MALLOC_SIZE(chats->chat_name)) {
            mx_del_strarr(&chats->chat_name);
        }
    }
    if (MALLOC_SIZE(chats))
        free(chats);
}

void contacts_json_creator(sqlite3 *db, t_json **json, int user) {
    t_contact *contacts = mx_db_get_contacts_info(db, user);

    (*json)->CONTACTS_ID_ARR = cJSON_CreateIntArray(contacts->id, contacts->count);
    (*json)->CONTACTS_LOGIN_ARR = cJSON_CreateStringArray((const char *const *) contacts->login, contacts->count);
    (*json)->CONTACTS_COUNT = cJSON_CreateNumber(contacts->count);

    cJSON_AddItemToObject((*json)->SEND, "CONTACTS_ID_ARR", (*json)->CONTACTS_ID_ARR);
    cJSON_AddItemToObject((*json)->SEND, "CONTACTS_LOGIN_ARR", (*json)->CONTACTS_LOGIN_ARR);
    cJSON_AddItemToObject((*json)->SEND, "CONTACTS_COUNT", (*json)->CONTACTS_COUNT);

    if (contacts->count > 0) {
        if (MALLOC_SIZE(contacts->id)) {
            free(contacts->id);
        }
        if (MALLOC_SIZE(contacts->login)) {
            mx_del_strarr(&contacts->login);
        }
    }
    if (MALLOC_SIZE(contacts))
        free(contacts);
}

void mx_login_and_pass_authentication(t_server *serv, t_json *json, int user_index) {
    char *send_str = NULL;

    json->SEND = cJSON_CreateObject();
    json->TYPE = cJSON_CreateNumber(AUTHENTICATION);

    json->USER_ID = cJSON_CreateNumber(mx_db_check_login(serv->db, json->LOGIN->valuestring, json->PASS->valuestring));
    if (json->USER_ID->valueint == 0 || json->USER_ID->valueint == -1) {
        json->RESULT = cJSON_CreateFalse(); // ошибка при входе в аккаунт - "0" - такой логин не существует, "-1" - неверный пароль
    }
    else {
        json->RESULT = cJSON_CreateTrue(); //аунтентификация прошла успешно
        contacts_json_creator(serv->db, &json, json->USER_ID->valueint);
        chats_json_creator(serv->db, &json, json->USER_ID->valueint);
        serv->users_id[user_index] = json->USER_ID->valueint;
        if (serv->cli_connect > 1) {
            serv->update = true;
        }
    }

    cJSON_AddItemToObject(json->SEND, "TYPE", json->TYPE);
    cJSON_AddItemToObject(json->SEND, "RESULT", json->RESULT);
    cJSON_AddItemToObject(json->SEND, "USER_ID", json->USER_ID);

    send_str = cJSON_Print(json->SEND);

    write(serv->user_socket[user_index], send_str, strlen(send_str));

    cJSON_Delete(json->SEND);
    free(send_str);
}
