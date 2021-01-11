//
// Created by mac on 08.01.2021.
//

#include "server.h"

void mx_serv_struct_initialization(t_server *serv) {
    serv->exit = false;
    serv->user_socket = (int *)malloc(sizeof(int) * MAX_CLIENTS);
    serv->cli_connect = 0;
    for (int k = 0; k < MAX_CLIENTS; k++) {
        serv->user_socket[k] = -1;
    }
}
