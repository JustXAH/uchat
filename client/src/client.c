//
// Created by Igor Khanenko on 12/20/20.
//

#include "client.h"

void *read_server(void *data) {
    char buff[MAX];
    t_client *cli = (t_client *) data;

    while (read(cli->sockfd, buff, sizeof(buff))) {
        write(1, buff, strlen(buff));
        if ((strncmp(buff, "exit", 4)) == 0) {
            write(1, "Client Exit\n", 12);
            break;
        }
        memset(buff, '\0', sizeof(buff));
    }
    return 0;
}

void func(int sockfd, t_client *cli) {
    char buff[MAX];
    int n;
    cJSON *LOGIN = cJSON_CreateString(cli->login);

    for (;;) {
        cJSON *send = cJSON_CreateObject();
        sleep(1);
        write(1, "\nEnter the string: ", 19);
        n = 0;
        while ((buff[n++] = getchar()) != '\n');
        if ((strncmp(buff, "exit", 4)) == 0) {
            write(1, "Client Exit\n", 12);
            break;
        }
        cJSON *MASSAGE = cJSON_CreateString(buff);
        cJSON_AddItemToObject(send, "LOGIN", LOGIN);
        cJSON_AddItemToObject(send, "massage", MASSAGE);
        write(sockfd, cJSON_Print(send), sizeof(buff));
        memset(buff, '\0', sizeof(buff));
    }
}

static void registration(t_client *cli) {
    char buff[20];

    write(1, "Please enter your login: ", 25);
    scanf("%s", buff);
    cli->login = strdup(buff);
    memset(buff, '\0', 20);
    write(1, "\nPlease enter your password: ", 29);
    scanf("%s", buff);
    cli->password = strdup(buff);
    memset(buff, '\0', 20);
    write(1, "\nPlease enter your nickname: ", 29);
    scanf("%s", buff);
    cli->nick = strdup(buff);
    memset(buff, '\0', 20);
    write(1, "\nPlease enter your birthday: ", 29);
    scanf("%s", buff);
    cli->birth = strdup(buff);
    memset(buff, '\0', 20);
}

int main(int argc, char *argv[]) {
    t_client *cli = (t_client *)malloc(sizeof(t_client));
    struct sockaddr_in servaddr;
    pthread_t thread;
    char *login_json;

    registration(cli);
    login_json = mx_create_json_profile(cli);

    // socket create and varification
    cli->sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (cli->sockfd == -1) {
        write(2, "ERROR, socket creation failed\n", 30);
        exit(0);
    }
    else
        write(1, "Socket successfully created...\n", 31);
    bzero(&servaddr, sizeof(servaddr));

    // assign IP, PORT
    servaddr.sin_family = AF_INET;
    if (argc == 2) {
        servaddr.sin_addr.s_addr = inet_addr(argv[1]);
    }
    else {
        servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    }
    servaddr.sin_port = htons(PORT);

    // connect the client socket to server socket
    if (connect(cli->sockfd, (SA*)&servaddr, sizeof(servaddr)) != 0) {
        write(2, "ERROR, connection with the server failed!\n", 42);
        exit(0);
    }
    else
        write(1, "Successfully connected to the server...\n", 40);

    write(cli->sockfd, login_json, mx_strlen(login_json));

    // function for chat
    pthread_create(&thread, NULL, read_server, cli);
    func(cli->sockfd, cli);

    // close the socket
    close(cli->sockfd);
}
