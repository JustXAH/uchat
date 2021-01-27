//
// Created by Igor Khanenko on 1/25/21.
//

#include "server.h"

void mx_update_handler(t_server *serv) {
    for (int i = 0; i != serv->cli_connect; i++) {
        if (serv->user_socket[i] != -1) {
            mx_sending_who_online(serv, i);
            printf("\nSent WHO ONLINE users id arr to this USER (SOCKET: %d; ID: %d)\n",
                   serv->users_id[i], serv->user_socket[i]);
        }
    }
}
