//
// Created by Igor Khanenko on 1/5/21.
//

#include "server.h"

void mx_user_registration(t_server *serv, char *u_login, char *u_pass, int user_sock) {
    cJSON *REGISTRATION = cJSON_CreateObject();
    cJSON *TYPE = cJSON_CreateNumber(3); //регистрация
    cJSON *RESULT = NULL; //результат аутентификации: FALSE - неудачно, TRUE - успешно
    cJSON *USER_ID = NULL;
    char *send = NULL;

    USER_ID = cJSON_CreateNumber(mx_db_insert_new_user(serv->db, u_login, u_pass));
    if (USER_ID->valueint == 0) {
        RESULT = cJSON_CreateFalse(); // ошибка при регистрации - логин уже существует
    }
    else {
        RESULT = cJSON_CreateTrue(); //регистрация прошла успешно
    }

    cJSON_AddItemToObject(REGISTRATION, "TYPE", TYPE);
    cJSON_AddItemToObject(REGISTRATION, "RESULT", RESULT);
    cJSON_AddItemToObject(REGISTRATION, "USER_ID", USER_ID);

    send = cJSON_Print(REGISTRATION);
    //send string-JSON to client
    write(user_sock, send, strlen(send));

    cJSON_Delete(REGISTRATION);
    free(send);
}
