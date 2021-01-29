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

static void add_new_contact_and_json_create(t_server *serv, t_json **json, int user_index, bool flag) {
    t_contact *contacts = NULL;
    int answer;
    char *send_str;

    if (flag == true)
        answer = mx_db_create_new_contact(serv->db, (*json)->USER_ID->valueint, (*json)->CONTACT_ID->valueint);
    else
        answer = mx_db_create_new_contact(serv->db, (*json)->CONTACT_ID->valueint, (*json)->USER_ID->valueint);
    if (answer == -1) {
        (*json)->RESULT = cJSON_CreateFalse();
    }
    else {
        if (flag)
            contacts = mx_db_get_contacts_info(serv->db, (*json)->USER_ID->valueint);
        else
            contacts = mx_db_get_contacts_info(serv->db, (*json)->CONTACT_ID->valueint);
        (*json)->CONTACTS_COUNT = cJSON_CreateNumber(contacts->count);
        (*json)->RESULT = cJSON_CreateTrue();
        (*json)->CONTACTS_ID_ARR = cJSON_CreateIntArray(contacts->id, contacts->count);
        (*json)->CONTACTS_LOGIN_ARR = cJSON_CreateStringArray((const char * const *)contacts->login, contacts->count);
    }
    cJSON_AddItemToObject((*json)->SEND, "RESULT", (*json)->RESULT);
    cJSON_AddItemToObject((*json)->SEND, "CONTACTS_ID_ARR", (*json)->CONTACTS_ID_ARR);
    cJSON_AddItemToObject((*json)->SEND, "CONTACTS_LOGIN_ARR", (*json)->CONTACTS_LOGIN_ARR);
    cJSON_AddItemToObject((*json)->SEND, "CONTACTS_COUNT", (*json)->CONTACTS_COUNT);

    send_str = cJSON_Print((*json)->SEND);
    if (flag == true)
        write(serv->user_socket[user_index], send_str, strlen(send_str));
    else
        which_user_online(serv, (*json), send_str);
    cJSON_Delete((*json)->SEND);
    free(send_str);

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
    json->USER_ID = cJSON_GetObjectItemCaseSensitive(json->USER_JSON, "USER_ID");
    json->CONTACT_ID = cJSON_GetObjectItemCaseSensitive(json->USER_JSON, "CONTACT_ID");

    json->SEND = cJSON_CreateObject();
    json->TYPE = cJSON_CreateNumber(NEW_CONTACT);
    cJSON_AddItemToObject(json->SEND, "TYPE", json->TYPE);
    add_new_contact_and_json_create(serv, &json, user_index, true);

    json->SEND = cJSON_CreateObject();
    json->TYPE = cJSON_CreateNumber(NEW_CONTACT);
    cJSON_AddItemToObject(json->SEND, "TYPE", json->TYPE);
    add_new_contact_and_json_create(serv, &json, user_index, false);
}
