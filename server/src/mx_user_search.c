//
// Created by mac on 09.01.2021.
//

#include "server.h"

void mx_user_search(t_server *serv, char *u_login, int user_sock) {
    cJSON *USER_SEARCH = cJSON_CreateObject();
    cJSON *TYPE = cJSON_CreateNumber(4); // log in - вход в аккаунт
    cJSON *RESULT = NULL; //результат аутентификации: FALSE - неудачно, TRUE - успешно
    cJSON *USER_ID = NULL;
    char *send = NULL;

    USER_ID = cJSON_CreateNumber(mx_db_check_login_exist(serv->db, u_login));
    if (USER_ID->valueint == 0) { // "0" - login doesn't exist
        RESULT = cJSON_CreateFalse();
    }
    else {
        RESULT = cJSON_CreateTrue(); //логин найден успешно
    }

    cJSON_AddItemToObject(USER_SEARCH, "TYPE", TYPE);
    cJSON_AddItemToObject(USER_SEARCH, "RESULT", RESULT);
    cJSON_AddItemToObject(USER_SEARCH, "USER_ID", USER_ID);

    send = cJSON_Print(USER_SEARCH);

    write(user_sock, send, strlen(send));

    cJSON_Delete(USER_SEARCH);
    free(send);
}
