//
// Created by Dima Voichuck on 12/25/20.
//

#include "server.h"

void mx_check_disconnect(t_server *serv, int i) {
    struct pollfd poll_set[2];
    int ret = 0;

    printf("------------------------------\n");
    printf("cli_connect = %d\n", serv->cli_connect);
    // от socket[i] мы будем ожидать входящих данных

    poll_set->fd = serv->user_socket[i];
    poll_set->events = POLLERR;


    // ждём до 1 секунд
    ret = poll(poll_set, serv->cli_connect, 1000);
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
        if (poll_set->revents & POLLERR) {
            // обработка входных данных от sock1
            poll_set->revents = 0;
            printf("socked_disconnect\n");
            serv->cli_connect--;
        }
    }
    printf("------------------------------\n");
}
