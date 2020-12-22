//
// Created by Igor Khanenko on 12/22/20.
//


#include "server.h"


//void *Accepting(void *data) {
//
//}

int main(int argc , char *argv[]) {
    int sockfd;
    int *cli_sockfd = (int *)malloc(sizeof(int) * 2);
    int c;
    int num_client = 0;
    int read_size;
    struct sockaddr_in server , client;
    char client_message[MAX];

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

    //Receive a message from client
    while(1) {
        //accept connection from an incoming client
        cli_sockfd[num_client] = accept(sockfd, (struct sockaddr *)&client, (socklen_t*)&c);
        if (cli_sockfd[num_client] < 0) {
            write(2, "ERROR, accept failed", 20);
            return 1;
        }
        else
            write(1, "Connection accepted!\n", 21);

        read(cli_sockfd[num_client] , client_message , sizeof(client_message));

        //Send the message back to client
        write(cli_sockfd[num_client], client_message , strlen(client_message));
        memset( &client_message, '\0', sizeof(client_message));
    }

    if(read_size == 0) {
        write(2, "Client disconnected", 19);
        fflush(stdout);
    }
    else if(read_size == -1) {
        perror("recv failed");
    }

    return 0;
}
