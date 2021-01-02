//
// Created by Igor Khanenko on 12/20/20.
//

#include "client.h"

void *read_server(void *data) {
    t_client *cli = (t_client *) data;
    char buff[MAX];
    cJSON *SERVER_JSON = NULL;
//    cJSON *SENDER = NULL;
    cJSON *MESSAGE = NULL;


    while (read(cli->sockfd, buff, sizeof(buff))) {
//        write(1, "\nFrom server: ", 14);
        SERVER_JSON = cJSON_Parse(buff);
//        SENDER = cJSON_GetObjectItemCaseSensitive(SERVER_JSON, "SENDER");
        MESSAGE = cJSON_GetObjectItemCaseSensitive(SERVER_JSON, "MESSAGE");

        write(1, cJSON_Print(MESSAGE), strlen(cJSON_Print(MESSAGE)));
        memset(buff, '\0', sizeof(buff));
//        cJSON_free(SERVER_JSON);
    }
    cJSON_Delete(SERVER_JSON);

    return 0;
}

void func(int sockfd, t_client *cli) {
    char buff[MAX];
    cJSON *SEND = cJSON_CreateObject();
    cJSON *TYPE = cJSON_CreateNumber(1);
    cJSON *LOGIN = cJSON_CreateString(cli->login);
    cJSON *MESSAGE = NULL;
//    bool first_entry = true;

    for (;;) {
//        cJSON *SEND = cJSON_CreateObject();
//        cJSON *TYPE = cJSON_CreateNumber(1);
//        cJSON *login = cJSON_CreateString(cli->login);

        sleep(1);
        write(1, "\n\nEnter your message: ", 22);
        scanf("%s", buff);
        if ((strcmp(buff, "exit")) == 0) {
            write(1, "Client Exit\n", 12);
            break;
        }
//            while ((buff[n++] = getchar()) != '\n');
//            if ((strncmp(buff, "exit", 4)) == 0) {
//                write(1, "Client Exit\n", 12);
//                break;
//            }
        MESSAGE = cJSON_CreateString(buff);
        cJSON_AddItemToObject(SEND, "TYPE", TYPE);
        cJSON_AddItemToObject(SEND, "LOGIN", LOGIN);
        cJSON_AddItemToObject(SEND, "MESSAGE", MESSAGE);
        write(sockfd, cJSON_Print(SEND), sizeof(buff));
        memset(buff, '\0', sizeof(buff));
        cJSON_free(MESSAGE);
    }
    cJSON_Delete(SEND);
}

static void authentication(t_client *cli) {
    char buff[20];

    write(1, "Please enter your username and password\n", 40);
    write(1, "Login: ", 7);
    scanf("%s", buff);
    cli->login = strdup(buff);
    memset(buff, '\0', 20);
    write(1, "Password: ", 10);
    scanf("%s", buff);
    cli->password = strdup(buff);
    memset(buff, '\0', 20);
//    write(1, "\nPlease enter your nickname: ", 29);
//    scanf("%s", buff);
//    cli->nick = strdup(buff);
//    memset(buff, '\0', 20);
//    write(1, "\nPlease enter your birthday: ", 29);
//    scanf("%s", buff);
//    cli->birth = strdup(buff);
//    memset(buff, '\0', 20);
}

int main(int argc, char *argv[]) {
    t_client *cli = (t_client *)malloc(sizeof(t_client));
    struct sockaddr_in servaddr;
    pthread_t thread;
    char *login_json;

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
        write(1, "Successfully connected to the server...\n\n", 41);

    authentication(cli);
    login_json = mx_create_user_profile(cli);
    write(cli->sockfd, login_json, mx_strlen(login_json));

    // function for chat
    pthread_create(&thread, NULL, read_server, cli);
    func(cli->sockfd, cli);

    // close the socket
    close(cli->sockfd);

    return 0;
}
