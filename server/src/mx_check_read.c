//
// Created by Dima Voichuck on 12/25/20.
//

#include "server.h"

static void read_and_write(t_server *serv, int i) {
    char client_message[MAX];
    char **str;
    cJSON *USER_JSON = NULL;
    cJSON *TYPE = NULL; //тип связи клиент-сервер (1 - сообщения, 2 - аутентификация, 3 - регистрация)
    cJSON *SENDER = NULL; // отправитель (логин)
    cJSON *MESSAGE = NULL;

    write(1, "Waiting for a message...\n", 25);
    read(serv->user_socket[i], client_message, MAX);
//        Send the message back to client
    if (client_message[0] != '\0') {
        USER_JSON = cJSON_Parse(client_message);
        TYPE = cJSON_GetObjectItemCaseSensitive(USER_JSON, "TYPE");

        if (TYPE->valueint == 2) { // аутентификация
            mx_login_and_pass_authentication(USER_JSON, serv->user_socket[i]);
        }
        else if (TYPE->valueint == 3) { // регистрация
            //ТУТ должна быть функция для регистрации пользователя
        }
        else { //это TYPE = 1 - сообщения!
            SENDER = cJSON_GetObjectItemCaseSensitive(USER_JSON, "SENDER");
            MESSAGE = cJSON_GetObjectItemCaseSensitive(USER_JSON, "MESSAGE");

            printf("Sender = %s\nmessage = %s\n", cJSON_Print(SENDER),
                   cJSON_Print(MESSAGE));
            str = mx_strsplit(MESSAGE->valuestring, ';');

            if (str[1] == NULL) {
                //ТУТ НАДО ИСПРАВЛЯТЬ ПОД JSON !!!
                write(serv->user_socket[i],
                      "Invalid  struct of message: Enter message and socket\n",
                      41);
            } else {
                printf("str[0] = %s, str[1] = %s", str[0], str[1]);
                printf("send message to client: '%s'\n", str[0]);
                //ТУТ НАДО ИСПРАВЛЯТЬ ПОД JSON !!!
                if (write(serv->user_socket[mx_atoi(str[1])], str[0],
                          strlen(str[0])) == -1)
                    write(serv->user_socket[i], "User not found", 16);
            }
            mx_del_strarr(&str);
            memset(&client_message, '\0', sizeof(client_message));
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
