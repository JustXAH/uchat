//
// Created by Igor Khanenko on 12/22/20.
//

#ifndef UCHAT_SERVER_H
#define UCHAT_SERVER_H

#include "cJSON.h"
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

#define MAX 4096
#define PORT 5000
#define MAX_CLIENTS 5

typedef struct s_server {
    int *user_socket;
    int serv_sock_fd;
    int cli_connect;
    bool exit;

}              t_server;

void mx_login_and_pass_authentication(cJSON *user_JSON, int user_sock);
void mx_user_registration(cJSON *user_JSON, int user_sock);
cJSON *mx_database_stub(cJSON *user);
void mx_read_server(t_server *serv);
void mx_check_read(t_server *serv, int i);
void mx_check_disconnect(t_server *server, int i);

#endif //UCHAT_SERVER_H
