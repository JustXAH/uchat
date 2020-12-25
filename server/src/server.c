//
// Created by Igor Khanenko on 12/22/20.
//

#include "cJSON.h"
#include "server.h"

void static read_and_write(t_server *serv, int i) {
    char client_message[MAX];
    char **str;

    write(1, "Waiting for a message...\n", 25);
    read(serv->user_socket[i], client_message, sizeof(client_message));
//        Send the message back to client
    str = mx_strsplit(client_message, ';');
    if (str[1] == NULL) {
//        free(str[0]);
        str[0] = mx_strdup("Message recipient is not specified!\nusage: message;user number(0,1,2,3,4)");
        printf("str[0] = %s, str[1] = %d", str[0], i);
        printf("send massage to client: '%s'\n", client_message);
        if (write(serv->user_socket[i], str[0],
                  strlen(str[0])) == -1)
            write(serv->user_socket[i], "User not found", 16);
//        str[1] = mx_strdup(mx_itoa(i));
    }
    else {
        printf("str[0] = %s, str[1] = %s", str[0], str[1]);
        printf("send massage to client: '%s'\n", client_message);
        if (write(serv->user_socket[mx_atoi(str[1])], str[0],
                  strlen(str[0])) == -1)
            write(serv->user_socket[i], "User not found", 16);
    }

    mx_del_strarr(&str);
    memset(&client_message, '\0', sizeof(client_message));
}

void* send_and_write(void *data) {
    t_server *serv = (t_server *) data;
    struct pollfd poll_set[2];
    int ret = 0;

    for (int i = 0; i != -1; ) {
        if (serv->cli_connect != 0) {
            if (i == serv->cli_connect) {
                i = 0;
            }
            printf("------------------------------\n");
            printf("cli_connect = %d\n", serv->cli_connect);
            // от socket[i] мы будем ожидать входящих данных

            poll_set->fd = serv->user_socket[i];
            poll_set->events = POLLIN;

            // ждём до 1 секунд
            ret = poll(poll_set, serv->cli_connect, 5000);
            printf("ret = %d\n", ret);
            printf("socket = %d[%d]\n", serv->user_socket[i], i);

            // проверяем успешность вызова
            if (ret == -1) {
                // ошибка
                printf("ERROR, poll checking client socket #%d\n", i);
            }
            else if (ret == 0) {
                // таймаут, событий не произошло
                write(1, "No events happened\n", 19);
            }
            else {
                // обнаружили событие, обнулим revents чтобы можно было переиспользовать структуру
                if (poll_set->revents & POLLIN) {
                    // обработка входных данных от sock1
                    poll_set->revents = 0;
                    read_and_write(serv, i);
                }
            }
            printf("------------------------------\n");
            i++;
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
    serv->cli_connect = 0;
    for (int k = 0; k < MAX_CLIENTS; k++) {
        serv->user_socket[k] = k + 4;
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
