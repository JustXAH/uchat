//
// Created by Igor Khanenko on 12/22/20.
//

#ifndef UCHAT_CLIENT_H
#define UCHAT_CLIENT_H

#include "cJSON.h"
#include "libmx.h"
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <pthread.h>
#include <poll.h>

#define MAX 4096
#define PORT 5000
#define SA struct sockaddr

typedef struct s_client {
    char *login;
    char *password;
    int sockfd;
//    pthread_mutex_t mutex;
    bool first_reg;
    bool authentication;
    bool registration;
}              t_client;


void mx_struct_initialization(t_client *cli);
void mx_login_or_register(t_client *cli);
char *mx_create_user_profile(t_client *cli, bool registration);
void mx_confirmation_of_registration(cJSON *SERVER_JSON, t_client *cli);
void mx_authentication_client(cJSON *SERVER_JSON, t_client *cli);

#endif //UCHAT_CLIENT_H
