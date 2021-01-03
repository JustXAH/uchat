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

typedef struct s_client {
    char *login;
    char *password;
    int sockfd;
    bool authentication;
//    char *nick;
//    char *birth;

}              t_client;

#define MAX 80
#define PORT 5000
#define SA struct sockaddr

char *mx_create_user_profile(t_client *cli);

#endif //UCHAT_CLIENT_H
