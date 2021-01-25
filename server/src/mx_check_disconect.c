//
// Created by Dima Voichuck on 12/25/20.
//

#include "server.h"

void mx_check_disconnect(t_server *serv, int user_index) {
    struct pollfd poll_set[1];
    int ret = 0;

    printf("------------------------------\n");
    printf("DISCONNECT\n");
    printf("cli_connect = %d\n", serv->cli_connect);
    // от socket[i] мы будем ожидать входящих данных

    poll_set->fd = serv->user_socket[user_index];
    poll_set->events = POLLHUP;

    // ждём до 1 секунд
    ret = poll(poll_set, 1, 1500);
    printf("ret = %d\n", ret);
    printf("socket = %d[%d]\n", serv->user_socket[user_index], user_index);

    // проверяем успешность вызова
    if (ret == -1) {
        // ошибка
        printf("ERROR, poll checking client socket #%d\n", user_index);
    }
    else if (ret == 0) {
        // таймаут, событий не произошло
        write(1, "No events happened\n", 19);
    }
    else {
        // обнаружили событие, обнулим revents чтобы можно было переиспользовать структуру
        if (poll_set->revents & POLLHUP) {
            // обработка входных данных от sock1
            poll_set->revents = 0;
            printf("socked_disconnect\n");
            serv->user_socket[user_index] = -1;
            mx_sorting_users_and_sockets(serv);
//            mx_int_bubble_sort_reverse(serv->user_socket, MAX_CLIENTS);
            serv->cli_connect -= 1;
            serv->update = true;
        }
    }
    printf("------------------------------\n");
}
