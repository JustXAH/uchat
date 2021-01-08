//
// Created by Igor Khanenko on 1/2/21.
//

#include "server.h"

void mx_login_and_pass_authentication(t_server *serv, char *u_login, char *u_pass, int user_sock) {
    cJSON *AUTHENTICATION = cJSON_CreateObject();
    cJSON *TYPE = cJSON_CreateNumber(2); // log in - вход в аккаунт
    cJSON *RESULT = NULL; //результат аутентификации: FALSE - неудачно, TRUE - успешно
    cJSON *USER_ID = NULL;
    char *send = NULL;

    USER_ID = cJSON_CreateNumber(mx_db_check_login(serv->db, u_login, u_pass));
    if (USER_ID->valueint == 0 || USER_ID->valueint == -1) {
        RESULT = cJSON_CreateFalse(); // ошибка при входе в аккаунт - "0" - такой логин не существует, "-1" - неверный пароль
    }
    else {
        RESULT = cJSON_CreateTrue(); //регистрация прошла успешно
    }

    cJSON_AddItemToObject(AUTHENTICATION, "TYPE", TYPE);
    cJSON_AddItemToObject(AUTHENTICATION, "RESULT", RESULT);
    cJSON_AddItemToObject(AUTHENTICATION, "USER_ID", USER_ID);

    send = cJSON_Print(AUTHENTICATION);

    write(user_sock, send, strlen(send));

    cJSON_Delete(AUTHENTICATION);
    free(send);
}
