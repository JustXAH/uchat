//
// Created by mac on 09.01.2021.
//

#include "server.h"

void mx_user_search_by_login(t_server *serv, char *u_login, int user_sock) {
    cJSON *SEND = cJSON_CreateObject();
    cJSON *TYPE = cJSON_CreateNumber(USER_SEARCH_BY_LOGIN);
    cJSON *RESULT = NULL; //результат аутентификации: FALSE - неудачно, TRUE - успешно
    cJSON *USER_ID = NULL;
    char *send_str = NULL;

    USER_ID = cJSON_CreateNumber(mx_db_check_login_exist(serv->db, u_login));
    if (USER_ID->valueint == 0) { // "0" - login doesn't exist
        RESULT = cJSON_CreateFalse();
    }
    else {
        RESULT = cJSON_CreateTrue(); //логин найден успешно
    }

    cJSON_AddItemToObject(SEND, "TYPE", TYPE);
    cJSON_AddItemToObject(SEND, "RESULT", RESULT);
    cJSON_AddItemToObject(SEND, "USER_ID", USER_ID);

    send_str = cJSON_Print(SEND);

    write(user_sock, send_str, strlen(send_str));

    cJSON_Delete(SEND);
    free(send_str);
}
