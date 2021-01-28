//
// Created by Igor Khanenko on 10.01.2021.
//

#include "server.h"

static void which_user_online(t_server *serv, t_json *json, char *send_str) {
    int contact_id = json->CONTACT_ID->valueint;

    for (int i = 0; serv->users_id[i]; i++)
        if (serv->users_id[i] == contact_id)
            write(serv->user_socket[i], send_str, strlen(send_str));
}

void add_new_contact_and_json_create(sqlite3 *db, t_json **json) {
    t_contact *contacts = NULL;
    int answer;

    answer = mx_db_create_new_contact(db, (*json)->USER_ID->valueint, (*json)->CONTACT_ID->valueint);
    if (answer == -1) {
        (*json)->RESULT = cJSON_CreateFalse();
    }
    else {
        contacts = mx_db_get_contacts_info(db, (*json)->USER_ID->valueint);
        (*json)->CONTACTS_COUNT = cJSON_CreateNumber(contacts->count);
        (*json)->RESULT = cJSON_CreateTrue();
        (*json)->CONTACTS_ID_ARR = cJSON_CreateIntArray(contacts->id, contacts->count);
        (*json)->CONTACTS_LOGIN_ARR = cJSON_CreateStringArray((const char * const *)contacts->login, contacts->count);
    }
    cJSON_AddItemToObject((*json)->SEND, "RESULT", (*json)->RESULT);
    cJSON_AddItemToObject((*json)->SEND, "CONTACTS_ID_ARR", (*json)->CONTACTS_ID_ARR);
    cJSON_AddItemToObject((*json)->SEND, "CONTACTS_LOGIN_ARR", (*json)->CONTACTS_LOGIN_ARR);
    cJSON_AddItemToObject((*json)->SEND, "CONTACTS_COUNT", (*json)->CONTACTS_COUNT);
    if (MALLOC_SIZE(contacts->id)) {
        free(contacts->id);
    }
    if (MALLOC_SIZE(contacts->login) && contacts->count > 0) {
        //Shit be segfaulting
       // mx_del_strarr(&contacts->login);
    }
    if (MALLOC_SIZE(contacts)) {
        free(contacts);
    }
}

void mx_add_new_contact(t_server *serv, t_json *json, int user_index) {
    char *send_str = NULL;
    json->USER_ID = cJSON_GetObjectItemCaseSensitive(json->USER_JSON, "USER_ID");
    json->CONTACT_ID = cJSON_GetObjectItemCaseSensitive(json->USER_JSON, "CONTACT_ID");
    json->SEND = cJSON_CreateObject();
    json->TYPE = cJSON_CreateNumber(NEW_CONTACT);

    cJSON_AddItemToObject(json->SEND, "TYPE", json->TYPE);
    add_new_contact_and_json_create(serv->db, &json);

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
//    result = mx_db_create_new_contact(db, user_id, contact_id);
//    if (result != -1) { // "-1" - an error occurred while creating a new contact
//        buff_arr = mx_db_get_chats(db, user_id);
//        arr_len = int_arr_len(buff_arr);
//        CONTACTS = cJSON_CreateIntArray(buff_arr, arr_len);
//        free(buff_arr);
//    }
//    return CONTACTS;
//}
