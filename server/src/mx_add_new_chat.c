//
// Created by Igor Khanenko on 10.01.2021.
//

#include "server.h"

void add_new_chat_and_json_create(sqlite3 *db, t_json **json) {
    t_chat *chats = NULL;
    int answer;

    answer = mx_db_create_new_chat(db, (*json)->USER_ID->valueint, (*json)->CONTACT_ID->valueint);
    if (answer == -1) {
        (*json)->RESULT = cJSON_CreateFalse();
    }
    else {
        (*json)->RESULT = cJSON_CreateTrue();
        chats = mx_db_get_chats_info(db, (*json)->USER_ID->valueint);
        (*json)->CHATS_ID_ARR = cJSON_CreateIntArray(chats->id, chats->count);
        (*json)->CHATS_NAME_ARR = cJSON_CreateStringArray((const char * const*)chats->chat_name, chats->count);
    }
    cJSON_AddItemToObject((*json)->SEND, "RESULT", (*json)->RESULT);
    cJSON_AddItemToObject((*json)->SEND, "CHATS_ID_ARR", (*json)->CHATS_ID_ARR);
    cJSON_AddItemToObject((*json)->SEND, "CHATS_NAME_ARR", (*json)->CHATS_NAME_ARR);

    if (MALLOC_SIZE(chats->id)) {
        free(chats->id);
    }
    if (MALLOC_SIZE(chats->chat_name)) {
        mx_del_strarr(&chats->chat_name);
    }
    free(chats);
}

void mx_add_new_chat(t_server *serv, t_json *json, int user_index) {
    char *send_str = NULL;

    json->USER_ID = cJSON_GetObjectItemCaseSensitive(json->USER_JSON, "USER_ID");
    json->CONTACT_ID = cJSON_GetObjectItemCaseSensitive(json->USER_JSON, "CONTACT_ID");
    json->SEND = cJSON_CreateObject();
    json->TYPE = cJSON_CreateNumber(NEW_CHAT);

    cJSON_AddItemToObject(json->SEND, "TYPE", json->TYPE);

    add_new_chat_and_json_create(serv->db, &json);

    send_str = cJSON_Print(json->SEND);

    write(serv->user_socket[user_index], send_str, strlen(send_str));

    cJSON_Delete(json->SEND);
    free(send_str);
}

//static int int_arr_len(const int *arr) {
//    int len = 0;
//
//    while (arr[len] != 0) {
//        len++;
//    }
//    return len;
//}
//
//static cJSON *json_id_arr_creator(sqlite3 *db, int user_id, int contact_id) {
//    cJSON *CONTACTS = NULL;
//    int *buff_arr;
//    int arr_len;
//    int result;
//
//    result = mx_db_create_new_chat(db, user_id, contact_id);
//    if (result != -1) { // "-1" - an error occurred while creating a new contact
//        buff_arr = mx_db_get_contacts(db, user_id);
//        arr_len = int_arr_len(buff_arr);
//        CONTACTS = cJSON_CreateIntArray(buff_arr, arr_len);
//        if (MALLOC_SIZE(buff_arr)) {
//            free(buff_arr);
//        }
//    }
//    return CONTACTS;
//}
//
//void mx_add_new_chat(t_server *serv, int user_id, int contact_id, int user_sock) {
//    cJSON *SEND = cJSON_CreateObject();
//    cJSON *TYPE = cJSON_CreateNumber(NEW_CHAT);
//    cJSON *RESULT = NULL; // результат аутентификации: FALSE - неудачно, TRUE - успешно
//    cJSON *CHATS_ID = NULL;
//    char *send_str = NULL;
//
//    CHATS_ID = json_id_arr_creator(serv->db, user_id, contact_id);
//    // if CHATS_ID == NULL - an error occurred while creating a new contact, else - successfully created a new contact
//    RESULT = CHATS_ID == NULL ? cJSON_CreateFalse() : cJSON_CreateTrue();
//
//    cJSON_AddItemToObject(SEND, "TYPE", TYPE);
//    cJSON_AddItemToObject(SEND, "RESULT", RESULT);
//    cJSON_AddItemToObject(SEND, "CHATS_ID", CHATS_ID);
//
//    send_str = cJSON_Print(SEND);
//
//    write(user_sock, send_str, strlen(send_str));
//
//    cJSON_Delete(SEND);
//    free(send_str);
//}
