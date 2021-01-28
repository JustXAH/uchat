//
// Created by mac on 08.01.2021.
//

#include "server.h"

void mx_serv_struct_initialization(t_server *serv) {
    serv->exit = false;
    serv->update = false;
    serv->user_socket = (int *)malloc(sizeof(int) * MAX_USERS);
    serv->users_id = (int *)malloc(sizeof(int) * MAX_USERS);
    serv->last_voice_send = (time_t *)malloc(sizeof(time_t) * MAX_USERS);
    serv->cli_connect = 0;
    for (int k = 0; k < MAX_USERS; k++) {
        serv->user_socket[k] = -1;
        serv->users_id[k] = -1;
        serv->last_voice_send[k] = time(0);
    }
}
