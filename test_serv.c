//
// Created by Igor Khanenko on 12/18/20.
//






//int main (int argc, char *argv[]) {
//    int listen_fd = 0;
//    int conn_fd = 0;
//    struct sockaddr_in serv_addr;
//    char sendBuff[1025];
//    time_t ticks;
//
//    listen_fd = socket(AF_INET, SOCK_STREAM, 0);
//    memset(&serv_addr, '0', sizeof(serv_addr));
//    memset(sendBuff, '0', sizeof(sendBuff));
//
//    serv_addr.sin_family = AF_INET;
//    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
//    serv_addr.sin_port = htons(5000);
//
//    bind(listen_fd, (struct sockaddr *) &serv_addr, sizeof(serv_addr));
//
//    listen(listen_fd, 10);
//
//    while (1) {
//        conn_fd = accept(listen_fd, (struct sockaddr *) NULL, NULL);
//
//
//
////        ticks = time(NULL);
////        snprintf(sendBuff, sizeof(sendBuff), "%.24s\r\n", ctime(&ticks));
////        write(conn_fd, sendBuff, strlen(sendBuff));
//
//        close(conn_fd);
////        usleep(1);
//    }
//}

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <time.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#define MAX 80
#define PORT 5000
#define SA struct sockaddr

// Function designed for chat between client and server.
void func(int sockfd) {
    char buff[MAX];
    int n;
    // infinite loop for chat
    for (;;) {
        bzero(buff, MAX);

        // read the message from client and copy it in buffer
        read(sockfd, buff, sizeof(buff));
        // print buffer which contains the client contents
        printf("From client: %s\t To client : ", buff);
        bzero(buff, MAX);
        n = 0;
        // copy server message in the buffer
        while ((buff[n++] = getchar()) != '\n');

        // and send that buffer to client
        write(sockfd, buff, sizeof(buff));

        // if msg contains "Exit" then server exit and chat ended.
        if (strncmp("exit", buff, 4) == 0) {
            printf("Server Exit...\n");
            break;
        }
    }
}

// Driver function
int main()
{
    int sockfd, connfd;
    unsigned int len;
    struct sockaddr_in servaddr, cli;
//    bool exit_trigger = false;

    // socket create and verification
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        printf("socket creation failed...\n");
        exit(0);
    }
    else
        printf("Socket successfully created..\n");
    bzero(&servaddr, sizeof(servaddr));

    // assign IP, PORT
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(PORT);

    // Binding newly created socket to given IP and verification
    if ((bind(sockfd, (SA*)&servaddr, sizeof(servaddr))) != 0) {
        printf("socket bind failed...\n");
        exit(0);
    }
    else
        printf("Socket successfully binded..\n");

    // Now server is ready to listen and verification
    if ((listen(sockfd, 5)) != 0) {
        printf("Listen failed...\n");
        exit(0);
    }
    else
        printf("Server listening..\n");
    len = sizeof(cli);

    // Accept the data packet from client and verification
    connfd = accept(sockfd, (SA*)&cli, &len);
    if (connfd < 0) {
        printf("server acccept failed...\n");
        exit(0);
    }
    else
        printf("server acccept the client...\n");

    // Function for chatting between client and server
    func(connfd);

    // After chatting close the socket
    close(sockfd);
}
