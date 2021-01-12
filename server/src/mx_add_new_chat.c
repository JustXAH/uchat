//
// Created by Igor Khanenko on 10.01.2021.
//

#include "server.h"

static int int_arr_len(const int *arr) {
    int len = 0;

    while (arr[len] != 0) {
        len++;
    }
    return len;
}

static cJSON *json_id_arr_creator(sqlite3 *db, int user_id, int contact_id) {
    cJSON *CONTACTS = NULL;
    int *buff_arr;
    int arr_len;
    int result;

    result = mx_db_create_new_chat(db, user_id, contact_id);
    if (result != -1) { // "-1" - an error occurred while creating a new contact
        buff_arr = mx_db_get_contacts(db, user_id);
        arr_len = int_arr_len(buff_arr);
        CONTACTS = cJSON_CreateIntArray(buff_arr, arr_len);
        if (MALLOC_SIZE(buff_arr)) {
            free(buff_arr);
        }
    }
    return CONTACTS;
}

void mx_add_new_chat(t_server *serv, int user_id, int contact_id, int user_sock) {
    cJSON *SEND = cJSON_CreateObject();
    cJSON *TYPE = cJSON_CreateNumber(NEW_CHAT);
    cJSON *RESULT = NULL; // результат аутентификации: FALSE - неудачно, TRUE - успешно
    cJSON *CHATS_ID = NULL;
    char *send_str = NULL;

    CHATS_ID = json_id_arr_creator(serv->db, user_id, contact_id);
    // if CHATS_ID == NULL - an error occurred while creating a new contact, else - successfully created a new contact
    RESULT = CHATS_ID == NULL ? cJSON_CreateFalse() : cJSON_CreateTrue();

    cJSON_AddItemToObject(SEND, "TYPE", TYPE);
    cJSON_AddItemToObject(SEND, "RESULT", RESULT);
    cJSON_AddItemToObject(SEND, "CHATS_ID", CHATS_ID);

    send_str = cJSON_Print(SEND);

    write(user_sock, send_str, strlen(send_str));

    cJSON_Delete(SEND);
    free(send_str);
}
