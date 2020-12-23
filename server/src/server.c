//
// Created by Igor Khanenko on 12/22/20.
//

#include "server.h"

void static read_and_write(t_server *serv, int i) {
    char client_message[MAX];

    write(1, "Waiting for a message...\n", 25);
    read(serv->user_socket[i], client_message, sizeof(client_message));
//        Send the message back to client
    printf("send massage to client: '%s'\n", client_message);
    write(serv->user_socket[i], client_message,
          strlen(client_message));
    memset(&client_message, '\0', sizeof(client_message));
}

void* send_and_write(void *data) {
    t_server *serv = (t_server *) data;
    struct pollfd fds[1];
    int ret = 0;

    for (int i = 0; i != -1; i++) {
        if (serv->cli_connect != 0) {
            if (i == serv->cli_connect) {
                i = 0;
            }
            // от socket[i] мы будем ожидать входящих данных
            fds[0].fd = serv->user_socket[i];
            fds[0].events = POLLIN;

            // ждём до 1 секунд
            ret = poll(fds, 2, 5000);
            // проверяем успешность вызова
            if (ret == -1) {
                // ошибка
                printf("ERROR, poll checking client socket #%d\n", i);
            }
            else if (ret == 0) {
                // таймаут, событий не произошло
                write(1, "No events happened\n", 19);
            }
            else
            {
                read_and_write(serv, i);
                // обнаружили событие, обнулим revents чтобы можно было переиспользовать структуру
                if (fds[0].revents & POLLIN)
                    fds[0].revents = 0;
                // обработка входных данных от sock1
            }
        }
    }
    return 0;
}

int main(int argc , char *argv[]) {
    int sockfd;
    int c;
    struct sockaddr_in server , client;
    pthread_t thread;
    t_server *serv = (t_server *)malloc(sizeof(t_server));

    serv->user_socket = (int *)malloc(sizeof(int) * MAX_CLIENTS);
    for (int k = 0; k < MAX_CLIENTS; k++) {
        serv->user_socket[k] = 0;
    }
    //Create socket
    sockfd = socket(AF_INET , SOCK_STREAM , 0);
    if (sockfd == -1) {
        write(2, "ERROR, could not create socket", 30);
    }
    write(1, "Socket created!\n", 16);

    //Prepare the sockaddr_in structure
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(PORT);

    //Bind
    if( bind(sockfd, (struct sockaddr *)&server , sizeof(server)) < 0) {
        //print the error message
        write(2, "ERROR, bind failed", 18);
        return 1;
    }
    write(1, "Socket successfully binded!\n", 28);

    //Listen
    listen(sockfd , 3);

    //Accept and incoming connection
    write(1, "Waiting for incoming connections...\n", 36);
    c = sizeof(struct sockaddr_in);

    pthread_create(&thread, NULL, send_and_write, serv);
    //Receive a message from client
    for (int i = 0; i != -1; ) {
        //accept connection from an incoming client
        serv->user_socket[i++] = accept(sockfd, (struct sockaddr *)&client, (socklen_t*)&c);
        serv->cli_connect += 1;

        if (serv->user_socket[i] < 0) {
            write(2, "ERROR, accept failed", 20);
            return 1;
        }
        else
            write(1, "Connection accepted!\n", 21);
    }

    return 0;
}
