//
// Created by Dima Voichuck on 12/25/20.
//

#include "server.h"

void mx_check_disconnect(t_server *serv, int user_index) {
    struct pollfd poll_set[1];
    int ret = 0;

    // от socket[i] мы будем ожидать входящих данных
    poll_set->fd = serv->user_socket[user_index];
    poll_set->events = POLLHUP;

    // ждём до 1 секунд
    ret = poll(poll_set, 1, 200);

    if (ret != -1 && ret != 0) {
        // обнаружили событие, обнулим revents чтобы можно было переиспользовать структуру
        if (poll_set->revents & POLLHUP) {
            // обработка входных данных от sock1
            poll_set->revents = 0;

            serv->user_socket[user_index] = -1;
            serv->users_id[user_index] = -1;
            serv->last_voice_send[user_index] = time(0);
            mx_sorting_users_and_sockets(serv);
            serv->cli_connect -= 1;
            serv->update = true;
        }
    }
}
