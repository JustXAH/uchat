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

static cJSON *json_id_arr_creator(sqlite3 *db, int user, int which) {
    cJSON *ID_ARR = NULL;
    int *buff_arr;
    int arr_len;

    if (which == 1) { // "1" - return cJSON array of contacts ID
        buff_arr = mx_db_get_contacts(db, user);
        arr_len = int_arr_len(buff_arr);
        ID_ARR = cJSON_CreateIntArray(buff_arr, arr_len);
    }
    else { // "2" - return cJSON array of chats ID
        buff_arr = mx_db_get_chats(db, user);
        arr_len = int_arr_len(buff_arr);
        ID_ARR = cJSON_CreateIntArray(buff_arr, arr_len);
    }
    free(buff_arr);
    return ID_ARR;
}

void mx_login_and_pass_authentication(t_server *serv, char *u_login, char *u_pass, int user_sock) {
    cJSON *AUTHENTICATION = cJSON_CreateObject();
    cJSON *TYPE = cJSON_CreateNumber(2); // log in - вход в аккаунт
    cJSON *RESULT = NULL; //результат аутентификации: FALSE - неудачно, TRUE - успешно
    cJSON *USER_ID = NULL;
    cJSON *CONTACTS_ID = NULL;
    cJSON *CHATS_ID = NULL;
    char *send = NULL;

//    mx_db_init(serv->db);
    USER_ID = cJSON_CreateNumber(mx_db_check_login(serv->db, u_login, u_pass));
    if (USER_ID->valueint == 0 || USER_ID->valueint == -1) {
        RESULT = cJSON_CreateFalse(); // ошибка при входе в аккаунт - "0" - такой логин не существует, "-1" - неверный пароль
    }
    else {
        RESULT = cJSON_CreateTrue(); //регистрация прошла успешно
        write(1, "\n1", 2);
//        CONTACTS_ID = json_id_arr_creator(serv->db, USER_ID->valueint, 1);
        write(1, "\n2", 2);
        CHATS_ID = json_id_arr_creator(serv->db, USER_ID->valueint, 2);
        write(1, "\n3", 2);
    }

    cJSON_AddItemToObject(AUTHENTICATION, "TYPE", TYPE);
    cJSON_AddItemToObject(AUTHENTICATION, "RESULT", RESULT);
    cJSON_AddItemToObject(AUTHENTICATION, "USER_ID", USER_ID);
    cJSON_AddItemToObject(AUTHENTICATION, "CONTACTS_ID", CONTACTS_ID);
    cJSON_AddItemToObject(AUTHENTICATION, "CHATS_ID", CHATS_ID);

    send = cJSON_Print(AUTHENTICATION);

    write(user_sock, send, strlen(send));

    cJSON_Delete(AUTHENTICATION);
    free(send);
}
