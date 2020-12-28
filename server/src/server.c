//
// Created by Igor Khanenko on 12/22/20.
//

#include "server.h"

void* poll_and_rw(void *data) {
    t_server *serv = (t_server *) data;


    for (int i = 0; serv->exit == true; ) {
//        mx_read_server(serv);
        if (serv->cli_connect != 0) {
            if (i == serv->cli_connect) {
                i = 0;
            }
//            mx_check_disconnect(serv, i);
            mx_check_read(serv, i);
            i++;
        }
    }
    return 0;
}

int main(int argc , char *argv[]) {
    int sockfd;
    int c;
    struct sockaddr_in server , client;
    char send_buff[1024];
    pthread_t thread;
    t_server *serv = (t_server *)malloc(sizeof(t_server));

    serv->exit = false;
    serv->user_socket = (int *)malloc(sizeof(int) * MAX_CLIENTS);
    serv->cli_connect = 0;
    for (int k = 0; k < MAX_CLIENTS; k++) {
        serv->user_socket[k] = -1;
    }
    //Create socket
    sockfd = socket(AF_INET , SOCK_STREAM , 0);
    if (sockfd == -1) {
        write(2, "ERROR, could not create socket", 30);
    }
    else {
        write(1, "Socket created!\n", 16);
        serv->serv_sock_fd = sockfd;
    }

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

    pthread_create(&thread, NULL, poll_and_rw, serv);
    //Receive a message from client
    for (int i = 0; serv->exit != true; i++) {
//        if (i == MAX_CLIENTS - 1)
//            i = 0;
        //accept connection from an incoming client
        serv->user_socket[i] = accept(sockfd, (struct sockaddr *) &client,
                                      (socklen_t *) &c);
        read(serv->user_socket[i], send_buff, sizeof(send_buff));

        cJSON *user = cJSON_Parse(send_buff);
        printf("%s\n", cJSON_Print(user));

        if (serv->user_socket[i] < 0) {
            write(2, "ERROR, accept failed", 20);
            return 1;
        }
        else {
            write(1, "Connection accepted!\n", 21);
            serv->cli_connect += 1;
        }
    }

    return 0;
}
