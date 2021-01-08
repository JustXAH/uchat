//
// Created by Dima Voichuck on 12/25/20.
//

#include "server.h"

static void read_and_write(t_server *serv, int user_num) {
    char buff_message[MAX];
    cJSON *USER_JSON = NULL;
    cJSON *TYPE = NULL; //тип связи клиент-сервер (1 - сообщения, 2 - аутентификация, 3 - регистрация)
    cJSON *LOGIN = NULL;
    cJSON *PASS = NULL;
    cJSON *MESSAGE = NULL;
    cJSON *TO = NULL;

    write(1, "Waiting for a message...\n", 25);
    read(serv->user_socket[user_num], buff_message, MAX);

//        Send the message back to client
    if (buff_message[0] != '\0') {
        USER_JSON = cJSON_Parse(buff_message);
        TYPE = cJSON_GetObjectItemCaseSensitive(USER_JSON, "TYPE");

        if (TYPE->valueint == 2) { // аутентификация
            LOGIN = cJSON_GetObjectItemCaseSensitive(USER_JSON, "LOGIN");
            PASS = cJSON_GetObjectItemCaseSensitive(USER_JSON, "PASS");
            mx_login_and_pass_authentication(serv, LOGIN->valuestring, PASS->valuestring, serv->user_socket[user_num]);
        }
        else if (TYPE->valueint == 3) { // регистрация
            LOGIN = cJSON_GetObjectItemCaseSensitive(USER_JSON, "LOGIN");
            PASS = cJSON_GetObjectItemCaseSensitive(USER_JSON, "PASS");
            mx_user_registration(serv, LOGIN->valuestring, PASS->valuestring, serv->user_socket[user_num]);
        }
        else { //это TYPE = 1 - сообщения!
            LOGIN = cJSON_GetObjectItemCaseSensitive(USER_JSON, "LOGIN");
            MESSAGE = cJSON_GetObjectItemCaseSensitive(USER_JSON, "MESSAGE");
            TO = cJSON_GetObjectItemCaseSensitive(USER_JSON, "TO");
            printf("Sender = %s\nmessage = %s\n", cJSON_Print(LOGIN),
                   cJSON_Print(MESSAGE));
            if (serv->cli_connect - 1 >= TO->valueint) {
                printf("%s\n", cJSON_Print(USER_JSON));
                write(serv->user_socket[TO->valueint], cJSON_Print(USER_JSON),
                      mx_strlen(cJSON_Print(USER_JSON)));
            }
            else {
                cJSON_DeleteItemFromObject(USER_JSON, "MESSAGE");
                cJSON_DeleteItemFromObject(USER_JSON, "TO");
                TO = cJSON_CreateString(mx_itoa(user_num));
                MESSAGE = cJSON_CreateString("User not found");
                cJSON_AddItemToObject(USER_JSON, "TO", TO);
                cJSON_AddItemToObject(USER_JSON, "MESSAGE", MESSAGE);
                printf("%s\n", cJSON_Print(USER_JSON));
                write(serv->user_socket[user_num], cJSON_Print(USER_JSON), mx_strlen(cJSON_Print(USER_JSON)));
            }
//            free(buff_message);
            memset(&buff_message, '\0', sizeof(buff_message));
        }
    }
    cJSON_Delete(USER_JSON);
}

void mx_check_read(t_server *serv, int i) {
    struct pollfd poll_set[1];
    int ret = 0;

    printf("------------------------------\n");
    printf("CHECK READ CLIENT SOCKET\n");
    printf("cli_connect = %d\n", serv->cli_connect);
    // от socket[i] мы будем ожидать входящих данных

    poll_set->fd = serv->user_socket[i];
    poll_set->events = POLLIN;

    // ждём до 1 секунд
    ret = poll(poll_set, 1, 3000);
    printf("ret = %d\n", ret);
    printf("socket = %d[%d]\n", serv->user_socket[i], i);

    // проверяем успешность вызова
    if (ret == -1) {
        // ошибка
        printf("ERROR, poll checking client socket #%d\n", i);
    }
    else if (ret == 0) {
        // таймаут, событий не произошло
        write(1, "No events happened\n", 19);
    }
    else {
        // обнаружили событие, обнулим revents чтобы можно было переиспользовать структуру
        if (poll_set->revents & POLLIN) {
            // обработка входных данных от sock1
            poll_set->revents = 0;
            read_and_write(serv, i);
        }
    }
    printf("------------------------------\n");
}
