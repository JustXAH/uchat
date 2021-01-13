//
// Created by Igor Khanenko on 1/5/21.
//

#include "server.h"

void mx_user_registration(t_server *serv, char *u_login, char *u_pass, int user_sock) {
    cJSON *SEND = cJSON_CreateObject();
    cJSON *TYPE = cJSON_CreateNumber(REGISTRATION);
    cJSON *RESULT = NULL; //результат аутентификации: FALSE - неудачно, TRUE - успешно
    cJSON *USER_ID = NULL;
    char *send_str = NULL;

    USER_ID = cJSON_CreateNumber(mx_db_insert_new_user(serv->db, u_login, u_pass));
    if (USER_ID->valueint == 0) {
        RESULT = cJSON_CreateFalse(); // ошибка при регистрации - логин уже существует
    }
    else {
        RESULT = cJSON_CreateTrue(); //регистрация прошла успешно
    }

    cJSON_AddItemToObject(SEND, "TYPE", TYPE);
    cJSON_AddItemToObject(SEND, "RESULT", RESULT);
    cJSON_AddItemToObject(SEND, "USER_ID", USER_ID);

    send_str = cJSON_Print(SEND);
    //send string-JSON to client
    write(user_sock, send_str, strlen(send_str));

    cJSON_Delete(SEND);
    free(send_str);
}
