//
// Created by Igor Khanenko on 1/2/21.
//

#include "server.h"

static int int_arr_len(const int *arr) {
    int len = 0;

    while (arr[len] != 0) {
        len++;
    }
    return len;
}

//static cJSON *json_id_arr_creator(sqlite3 *db, int user, int which) {
//    cJSON *ID_ARR = NULL;
//    int *buff_arr;
//    int arr_len;
//
//    if (which == 1) { // "1" - return cJSON array of contacts ID
//        buff_arr = mx_db_get_contacts(db, user);
//        arr_len = int_arr_len(buff_arr);
//        ID_ARR = cJSON_CreateIntArray(buff_arr, arr_len);
//    }
//    else { // "2" - return cJSON array of chats ID
//        buff_arr = mx_db_get_chats(db, user);
//        arr_len = int_arr_len(buff_arr);
//        ID_ARR = cJSON_CreateIntArray(buff_arr, arr_len);
//    }
//    free(buff_arr);
//    return ID_ARR;
//}

void chats_json_creator(sqlite3 *db, int user, cJSON **SEND) {
    t_chats *chats = mx_db_get_chats_info(db, user);
    cJSON *CHATS_ID = cJSON_CreateIntArray(chats->id, chats->count);;
    cJSON *CHATS_NAME = cJSON_CreateStringArray((const char **)chats->chat_name, chats->count);

    cJSON_AddItemToObject((*SEND), "CHATS_ID", CHATS_ID);
    cJSON_AddItemToObject((*SEND), "CHATS_NAME", CHATS_NAME);

    if (malloc_size(chats->id)) {
        free(chats->id);
    }
    if (malloc_size(chats->chat_name)) {
        mx_del_strarr(&chats->chat_name);
    }
    free(chats);
}

void contacts_json_creator(sqlite3 *db, int user, cJSON **SEND) {
    t_contacts *contacts = mx_db_get_contacts_info(db, user);
    cJSON *CONTACTS_ID = cJSON_CreateIntArray(contacts->id, contacts->count);
    cJSON *CONTACTS_LOGIN = cJSON_CreateStringArray((const char **)contacts->login, contacts->count);

    cJSON_AddItemToObject((*SEND), "CONTACTS_ID", CONTACTS_ID);
    cJSON_AddItemToObject((*SEND), "CONTACTS_LOGIN", CONTACTS_LOGIN);

    if (malloc_size(contacts->id)) {
        free(contacts->id);
    }
    if (malloc_size(contacts->login)) {
        mx_del_strarr(&contacts->login);
    }
    free(contacts);
}

void mx_login_and_pass_authentication(t_server *serv, char *u_login, char *u_pass, int user_sock) {
    cJSON *SEND = cJSON_CreateObject();
    cJSON *TYPE = cJSON_CreateNumber(AUTHENTICATION);
    cJSON *RESULT = NULL; //результат аутентификации: FALSE - неудачно, TRUE - успешно
    cJSON *USER_ID = NULL;

    char *send_str = NULL;

//    mx_db_init(serv->db);
    USER_ID = cJSON_CreateNumber(mx_db_check_login(serv->db, u_login, u_pass));
    if (USER_ID->valueint == 0 || USER_ID->valueint == -1) {
        RESULT = cJSON_CreateFalse(); // ошибка при входе в аккаунт - "0" - такой логин не существует, "-1" - неверный пароль
    }
    else {
        RESULT = cJSON_CreateTrue(); //регистрация прошла успешно
        contacts_json_creator(serv->db, USER_ID->valueint, &SEND);
        chats_json_creator(serv->db, USER_ID->valueint, &SEND);
//        CONTACTS_ID = json_id_arr_creator(serv->db, USER_ID->valueint, 1);
//        CHATS_ID = json_id_arr_creator(serv->db, USER_ID->valueint, 2);
    }

    cJSON_AddItemToObject(SEND, "TYPE", TYPE);
    cJSON_AddItemToObject(SEND, "RESULT", RESULT);
    cJSON_AddItemToObject(SEND, "USER_ID", USER_ID);

    send_str = cJSON_Print(SEND);

    write(user_sock, send_str, strlen(send_str));

    cJSON_Delete(SEND);
    free(send_str);
}
