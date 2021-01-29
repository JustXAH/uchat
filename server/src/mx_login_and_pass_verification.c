//
// Created by Igor Khanenko on 1/2/21.
//

#include "server.h"

static void voices_json_creator(sqlite3 *db, t_json **json, int user) {
    t_voice *voice = mx_db_get_users_voices(db, user);
    int count = 0;

    for (int k = 0; k < NUMBER_VOICES; k++) {
        if (voice->voice_name == NULL) {
            break;
        }
        if (voice->voice_name[k] != NULL) {
            count++;
        }
    }
    (*json)->VOICES_ID_ARR = cJSON_CreateIntArray(voice->id, NUMBER_VOICES);
    (*json)->VOICES_NAME_ARR = cJSON_CreateStringArray(
            (const char *const *) voice->voice_name, count);
    cJSON_AddItemToObject((*json)->SEND, "VOICES_ID_ARR",
                          (*json)->VOICES_ID_ARR);
    cJSON_AddItemToObject((*json)->SEND, "VOICES_NAME_ARR",
                          (*json)->VOICES_NAME_ARR);

    if (MALLOC_SIZE(voice->id)) {
        free(voice->id);
    }
    if (MALLOC_SIZE(voice->voice_name)) {
        for (int i = 0; i != NUMBER_VOICES; i++) {
            if (voice->voice_name[i] != NULL) {
                mx_strdel(&voice->voice_name[i]);
            }
        }
        free(voice->voice_name);
    }
    if (MALLOC_SIZE(voice))
        free(voice);
}

static void chats_json_creator(sqlite3 *db, t_json **json, int user) {
    t_chat *chats = mx_db_get_chats_info(db, user);

    (*json)->CHATS_ID_ARR = cJSON_CreateIntArray(chats->id, chats->count);
    (*json)->CHATS_NAME_ARR = cJSON_CreateStringArray(
            (const char *const *) chats->chat_name, chats->count);
    (*json)->CHATS_COUNT = cJSON_CreateNumber(chats->count);
    (*json)->NOTIFICATION = cJSON_CreateIntArray(chats->notification, chats->count);

    cJSON_AddItemToObject((*json)->SEND, "CHATS_ID_ARR",
                          (*json)->CHATS_ID_ARR);
    cJSON_AddItemToObject((*json)->SEND, "CHATS_NAME_ARR",
                          (*json)->CHATS_NAME_ARR);
    cJSON_AddItemToObject((*json)->SEND, "CHATS_COUNT",
                          (*json)->CHATS_COUNT);
    cJSON_AddItemToObject((*json)->SEND, "NOTIFICATION",
                          (*json)->NOTIFICATION);

    if (chats->count > 0) {
        if (MALLOC_SIZE(chats->id)) {
            free(chats->id);
        }
        if (MALLOC_SIZE(chats->chat_name)) {
            for (int i = 0; i != chats->count; i++) {
                if (chats->chat_name[i] != NULL) {
                    mx_strdel(&chats->chat_name[i]);
                }
            }
            free(chats->chat_name);
        }
    }
    if (MALLOC_SIZE(chats))
        free(chats);
}

static void contacts_json_creator(sqlite3 *db, t_json **json, int user) {
    t_contact *contacts = mx_db_get_contacts_info(db, user);

    (*json)->CONTACTS_ID_ARR = cJSON_CreateIntArray(contacts->id,
                                                    contacts->count);
    (*json)->CONTACTS_LOGIN_ARR = cJSON_CreateStringArray(
            (const char *const *) contacts->login, contacts->count);
    (*json)->CONTACTS_COUNT = cJSON_CreateNumber(contacts->count);

    cJSON_AddItemToObject((*json)->SEND, "CONTACTS_ID_ARR",
                          (*json)->CONTACTS_ID_ARR);
    cJSON_AddItemToObject((*json)->SEND, "CONTACTS_LOGIN_ARR",
                          (*json)->CONTACTS_LOGIN_ARR);
    cJSON_AddItemToObject((*json)->SEND, "CONTACTS_COUNT",
                          (*json)->CONTACTS_COUNT);

    if (contacts->count > 0) {
        if (MALLOC_SIZE(contacts->id)) {
            free(contacts->id);
        }
        if (MALLOC_SIZE(contacts->login)) {
            for (int i = 0; i != contacts->count; i++) {
                if (contacts->login[i] != NULL) {
                    mx_strdel(&contacts->login[i]);
                }
            }
            free(contacts->login);
        }
    }
    if (MALLOC_SIZE(contacts))
        free(contacts);
}

void mx_login_and_pass_authentication(t_server *serv, t_json *json, int user_index) {
    char *send_str = NULL;

    json->LOGIN = cJSON_GetObjectItemCaseSensitive(json->USER_JSON, "LOGIN");
    json->PASS = cJSON_GetObjectItemCaseSensitive(json->USER_JSON, "PASS");
    json->SEND = cJSON_CreateObject();
    json->TYPE = cJSON_CreateNumber(AUTHENTICATION);

    json->USER_ID = cJSON_CreateNumber(
            mx_db_check_login(serv->db, json->LOGIN->valuestring,
                              json->PASS->valuestring));
    if (json->USER_ID->valueint == 0 || json->USER_ID->valueint == -1) {
        // ошибка при входе в аккаунт - "0" - логин не существует, "-1" - неверный пароль
        json->RESULT = cJSON_CreateFalse();
    } else {
        json->RESULT = cJSON_CreateTrue(); //аунтентификация прошла успешно
        contacts_json_creator(serv->db, &json, json->USER_ID->valueint);
        chats_json_creator(serv->db, &json, json->USER_ID->valueint);
        voices_json_creator(serv->db, &json, json->USER_ID->valueint);
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
