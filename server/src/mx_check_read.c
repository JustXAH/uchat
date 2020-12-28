//
// Created by Dima Voichuck on 12/25/20.
//

#include "server.h"

static void read_and_write(t_server *serv, int i) {
    char client_message[MAX];
    char **str;

    write(1, "Waiting for a message...\n", 25);
    read(serv->user_socket[i], client_message, sizeof(client_message));
//        Send the message back to client
    str = mx_strsplit(client_message, ';');
    if (str[1] == NULL) {
//        free(str[0]);
        str[0] = mx_strdup("Message recipient is not specified!\nusage: message;user number(0,1,2,3,4)");
        printf("str[0] = %s, str[1] = %d", str[0], i);
        printf("send massage to client: '%s'\n", client_message);
        if (write(serv->user_socket[i], str[0],
                  strlen(str[0])) == -1)
            write(serv->user_socket[i], "User not found", 16);
//        str[1] = mx_strdup(mx_itoa(i));
    }
    else {
        printf("str[0] = %s, str[1] = %s", str[0], str[1]);
        printf("send massage to client: '%s'\n", client_message);
        if (write(serv->user_socket[mx_atoi(str[1])], str[0],
                  strlen(str[0])) == -1)
            write(serv->user_socket[i], "User not found", 16);
    }
    mx_del_strarr(&str);
    memset(&client_message, '\0', sizeof(client_message));
}

void mx_check_read(t_server *serv, int i) {
    struct pollfd poll_set[1];
    int ret = 0;

    printf("------------------------------\n");
    printf("cli_connect = %d\n", serv->cli_connect);
    // от socket[i] мы будем ожидать входящих данных

    poll_set->fd = serv->user_socket[i];
    poll_set->events = POLLIN;

//    poll_set[1].fd = serv->user_socket[i];
//    poll_set[1].events = POLLHUP;


    // ждём до 1 секунд
    ret = poll(poll_set, serv->cli_connect, 1);
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
//        if (poll_set->revents & POLLHUP) {
//            serv->cli_connect -= 1;
//        }
    }
    printf("------------------------------\n");
}
