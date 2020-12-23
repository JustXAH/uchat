//
// Created by Igor Khanenko on 12/22/20.
//

#ifndef UCHAT_SERVER_H
#define UCHAT_SERVER_H

#include "libmx.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <poll.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <pthread.h>
#include <time.h>

#define MAX 1024
#define PORT 5001
#define MAX_CLIENTS 5

typedef struct s_server {
    int *user_socket;
    int cli_connect;

}              t_server;

#endif //UCHAT_SERVER_H
