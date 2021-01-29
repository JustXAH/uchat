
//
// Created by dima on 15.01.2021.
//

#include "client.h"

extern t_client_st cl_listener;

static void add_contacts_login(t_user *user, cJSON *CONTACTS_LOGIN_ARR) {
    user->contacts_login = (char **)malloc(sizeof(char *) * (user->contacts_count + 1));
    for (int i = 0; i != user->contacts_count; i++) {
        user->contacts_login[i] = mx_strdup(cJSON_GetArrayItem(CONTACTS_LOGIN_ARR, i)->valuestring);
    }
    user->contacts_login[user->contacts_count] = NULL;
}

static void add_contacts_id(t_user *user, cJSON *CONTACTS_ID_ARR) {
    user->contacts_id = (int *)malloc(sizeof(int) * user->contacts_count);
    for (int i = 0; i != user->contacts_count; i++) {
        user->contacts_id[i] = cJSON_GetArrayItem(CONTACTS_ID_ARR, i)->valueint;
    }
}

void mx_add_new_contact(t_system *sys, t_user *user, t_json *json) {
    json->RESULT = cJSON_GetObjectItemCaseSensitive(json->SERVER_JSON, "RESULT");
    json->CONTACTS_ID_ARR = cJSON_GetObjectItemCaseSensitive(json->SERVER_JSON, "CONTACTS_ID_ARR");
    json->CONTACTS_LOGIN_ARR = cJSON_GetObjectItemCaseSensitive(json->SERVER_JSON, "CONTACTS_LOGIN_ARR");
    json->CONTACTS_COUNT = cJSON_GetObjectItemCaseSensitive(json->SERVER_JSON, "CONTACTS_COUNT");
    if (cJSON_IsFalse(json->RESULT)) {
       // вызов всплывающего текста c ошибкой
    }
    else {
        user->contacts_count = json->CONTACTS_COUNT->valueint;
        if (MALLOC_SIZE(user->contacts_id)) {
            free(user->contacts_id);
        }
        add_contacts_id(user, json->CONTACTS_ID_ARR);
        if (MALLOC_SIZE(user->contacts_login)) {
            free(user->contacts_login);
        }
        add_contacts_login(user, json->CONTACTS_LOGIN_ARR);
    }
    cJSON_DeleteItemFromObject(json->SERVER_JSON, "RESULT");
    cJSON_DeleteItemFromObject(json->SERVER_JSON, "CONTACTS_COUNT");
    cJSON_DeleteItemFromObject(json->SERVER_JSON, "CONTACTS_ID_ARR");
    cJSON_DeleteItemFromObject(json->SERVER_JSON, "CONTACTS_LOGIN_ARR");

    //cl_listener.new_contact_received = true;
    int cont_i = user->contacts_count - 1;
    mb_contact_list_add(user->contacts_id[cont_i], user->contacts_login[cont_i], false);
}
