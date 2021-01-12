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

    result = mx_db_create_new_contact(db, user_id, contact_id);
    if (result != -1) { // "-1" - an error occurred while creating a new contact
        buff_arr = mx_db_get_chats(db, user_id);
        arr_len = int_arr_len(buff_arr);
        CONTACTS = cJSON_CreateIntArray(buff_arr, arr_len);
        free(buff_arr);
    }
    return CONTACTS;
}

void mx_add_new_contact(t_server *serv, int user_id, int contact_id, int user_sock) {
    cJSON *NEW_CONTACT = cJSON_CreateObject();
    cJSON *TYPE = cJSON_CreateNumber(5); // create new contact
    cJSON *RESULT = NULL; // результат аутентификации: FALSE - неудачно, TRUE - успешно
    cJSON *CONTACTS_ID = NULL;
    char *send = NULL;

    CONTACTS_ID = json_id_arr_creator(serv->db, user_id, contact_id);
    // if CONTACTS_ID == NULL - an error occurred while creating a new contact, else - successfully created a new contact
    RESULT = CONTACTS_ID == NULL ? cJSON_CreateFalse() : cJSON_CreateTrue();

    cJSON_AddItemToObject(NEW_CONTACT, "TYPE", TYPE);
    cJSON_AddItemToObject(NEW_CONTACT, "RESULT", RESULT);
    cJSON_AddItemToObject(NEW_CONTACT, "CONTACTS_ID", CONTACTS_ID);

    send = cJSON_Print(NEW_CONTACT);

    write(user_sock, send, strlen(send));

    cJSON_Delete(NEW_CONTACT);
    free(send);
}
