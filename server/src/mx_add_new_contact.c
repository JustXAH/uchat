//
// Created by Igor Khanenko on 10.01.2021.
//

#include "server.h"

void add_new_contact_and_json_create(sqlite3 *db, int user_id, int contact_id, cJSON **SEND) {
    t_contact *contacts = NULL;
    cJSON *RESULT = NULL;
    cJSON *CONTACTS_ID = NULL;
    cJSON *CONTACTS_LOGIN = NULL;
    int answer = 0;

    answer = mx_db_create_new_contact(db, user_id, contact_id);
    if (answer == -1) {
        RESULT = cJSON_CreateFalse();
    }
    else {
        RESULT = cJSON_CreateTrue();
        contacts = mx_db_get_contacts_info(db, user_id);
        CONTACTS_ID = cJSON_CreateIntArray(contacts->id, contacts->count);
        CONTACTS_LOGIN = cJSON_CreateStringArray((const char **)contacts->login, contacts->count);
    }
    cJSON_AddItemToObject((*SEND), "RESULT", RESULT);
    cJSON_AddItemToObject((*SEND), "CONTACTS_ID", CONTACTS_ID);
    cJSON_AddItemToObject((*SEND), "CONTACTS_LOGIN", CONTACTS_LOGIN);

    if (MALLOC_SIZE(contacts->id)) {
        free(contacts->id);
    }
    if (MALLOC_SIZE(contacts->login)) {
        mx_del_strarr(&contacts->login);
    }
    free(contacts);
}

void mx_add_new_contact(t_server *serv, int user_id, int contact_id, int user_sock) {
    cJSON *SEND = cJSON_CreateObject();
    cJSON *TYPE = cJSON_CreateNumber(NEW_CONTACT);
    char *send_str = NULL;

    add_new_contact_and_json_create(serv->db, user_id, contact_id, &SEND);

    cJSON_AddItemToObject(SEND, "TYPE", TYPE);

    send_str = cJSON_Print(SEND);

    write(user_sock, send_str, strlen(send_str));

    cJSON_Delete(SEND);
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
//    result = mx_db_create_new_contact(db, user_id, contact_id);
//    if (result != -1) { // "-1" - an error occurred while creating a new contact
//        buff_arr = mx_db_get_chats(db, user_id);
//        arr_len = int_arr_len(buff_arr);
//        CONTACTS = cJSON_CreateIntArray(buff_arr, arr_len);
//        free(buff_arr);
//    }
//    return CONTACTS;
//}
