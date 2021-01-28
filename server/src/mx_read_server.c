//
// Created by Igor Khanenko on 12/28/20.
//

#include "server.h"

void mx_read_server(t_server *serv) {
    char buff[MAX_LEN];

    while (read(0, buff, sizeof(buff))) {
        write(1, buff, strlen(buff));
        if ((strncmp(buff, "exit", 4)) == 0) {
            write(1, "Server Exit\n", 12);
            serv->exit = true;
            break;
        }
        bzero(buff, sizeof(buff));
    }
}
