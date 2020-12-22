//
// Created by Igor Khanenko on 12/18/20.
//
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <time.h>


int main (int argc, char *argv[]) {
    int listen_fd = 0;
    int conn_fd = 0;
    struct sockaddr_in serv_addr;
    char sendBuff[1025];
    char *str;
    FILE *fp;
    char ch;

    listen_fd = socket(AF_INET, SOCK_STREAM, 0);
    memset(&serv_addr, '0', sizeof(serv_addr));
    memset(sendBuff, '0', sizeof(sendBuff));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(5000);

    bind(listen_fd, (struct sockaddr *) &serv_addr, sizeof(serv_addr));

    listen(listen_fd, 10);
    while (1) {
        conn_fd = accept(listen_fd, (struct sockaddr *) NULL, NULL);
        send(conn_fd, "Enter text:", 12, 0);
        if (recv(conn_fd, sendBuff, sizeof(sendBuff), MSG_PEEK))
            printf("%s\n", sendBuff);
        sleep(1);
    }
}