//
// Created by Igor Khanenko on 12/20/20.
//

#include "client.h"

void *read_server(void *data) {
    t_client *cli = (t_client *) data;
    char buff[MAX];
    char *str_user_json;
    cJSON *SERVER_JSON = NULL;
    cJSON *TYPE = NULL;
    cJSON *RESULT = NULL;
    cJSON *SENDER = NULL;
    cJSON *MESSAGE = NULL;

//    char *str = NULL;

    while (read(cli->sockfd, buff, sizeof(buff))) {
        printf("%s\n", buff);
//        write(1, "\nFrom %", 6);
//        printf("%s\n", buff);
        SERVER_JSON = cJSON_Parse(buff);
        TYPE = cJSON_GetObjectItemCaseSensitive(SERVER_JSON, "TYPE");
        if (TYPE != NULL) {
            if (TYPE->valueint == 2) { //аутентификация
                RESULT = cJSON_GetObjectItemCaseSensitive(SERVER_JSON,
                                                          "RESULT");
                MESSAGE = cJSON_GetObjectItemCaseSensitive(SERVER_JSON,
                                                           "MESSAGE");
                printf("\n%s", MESSAGE->valuestring);
                if (cJSON_IsFalse(RESULT)) {
                    if (malloc_size(cli->login)) {
                        free(cli->login);
                    }
                    if (malloc_size(cli->password)) {
                        free(cli->password);
                    }
                    str_user_json = mx_create_user_profile(cli);
                    write(cli->sockfd, str_user_json, strlen(str_user_json));
                    free(str_user_json);
                } else { //RESULT = TRUE (аутентификация прошла успеexitшно)
                    cli->authentication = true;
                }
                cJSON_DeleteItemFromObject(SERVER_JSON, "RESULT");
            } else { //TYPE == 1 (сообщения)
                SENDER = cJSON_GetObjectItemCaseSensitive(SERVER_JSON,
                                                          "LOGIN");
                MESSAGE = cJSON_GetObjectItemCaseSensitive(SERVER_JSON,
                                                           "MESSAGE");
//        write (1, SENDER->valuestring, strlen(SENDER->valuestring));
                printf("\nFrom %s: %s", SENDER->valuestring,
                       MESSAGE->valuestring);

//        str = mx_strdup(MESSAGE->valuestring);
//        write(1, str, mx_strlen(str));

//        free(str);
                cJSON_DeleteItemFromObject(SERVER_JSON, "LOGIN");
//            cJSON_free(SENDER);
//            cJSON_free(SERVER_JSON);
            }
            cJSON_DeleteItemFromObject(SERVER_JSON, "TYPE");
            cJSON_DeleteItemFromObject(SERVER_JSON, "TO");
            cJSON_DeleteItemFromObject(SERVER_JSON, "MESSAGE");
//        cJSON_free(MESSAGE);
            memset(buff, '\0', sizeof(buff));
        }
        cJSON_Delete(SERVER_JSON);
    }
    return 0;
}

void func(int sockfd, t_client *cli, pthread_t thread) {
    char buff[MAX];
    char **split_str;
    char *str_send;
    cJSON *SEND = cJSON_CreateObject();
    cJSON *TYPE = cJSON_CreateNumber(1);
    cJSON *LOGIN = cJSON_CreateString(cli->login);
    cJSON *TO = NULL;
    cJSON *MESSAGE = NULL;
//    int n = 0;

//    bool first_entry = true;
//    if (cli->authentication == true) {
        for (;;) {
//        cJSON *SEND = cJSON_CreateObject();
//        cJSON *TYPE = cJSON_CreateNumber(1);
//        cJSON *login = cJSON_CreateString(cli->login);

            sleep(1);
            write(1, "\n\nEnter your message: ", 22);
            scanf("%s", buff);
//        while ((buff[n++] = getchar()) != '\n');
//        n = 0;
            if ((strncmp(buff, "exit", 4)) == 0) {
                write(1, "Client Exit\n", 12);
                pthread_cancel(thread);
                break;
            } else {
                split_str = mx_strsplit(buff, ';');
                if (split_str[1] == NULL)
                    write(1,
                          "\nERROR, invalid  struct of message.\nusage: [message][;][socket]",
                          64);
                else {
                    mx_del_char(split_str[1], mx_strlen(split_str[1]) - 1,
                                '\n');
                    MESSAGE = cJSON_CreateString(split_str[0]);
                    TO = cJSON_CreateNumber(mx_atoi(split_str[1]));
                    cJSON_AddItemToObject(SEND, "TYPE", TYPE);
                    cJSON_AddItemToObject(SEND, "LOGIN", LOGIN);
                    cJSON_AddItemToObject(SEND, "MESSAGE", MESSAGE);
                    cJSON_AddItemToObject(SEND, "TO", TO);
                    str_send = cJSON_Print(SEND);
//                printf("\n\nJSON send to server:%s\n\n", str_send);
                    write(sockfd, str_send, strlen(str_send));
                    cJSON_DeleteItemFromObject(SEND, "MESSAGE");
                    cJSON_DeleteItemFromObject(SEND, "TO");
                    if (malloc_size(str_send))
                        free(str_send);
                }
                mx_del_strarr(&split_str);
                memset(buff, '\0', sizeof(buff));
            }
        }
        cJSON_Delete(SEND);
//    }
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

//    authentication(cli);
    login_json = mx_create_user_profile(cli);
    write(cli->sockfd, login_json, mx_strlen(login_json));

    // function for chat
    pthread_create(&thread, NULL, read_server, cli);
    func(cli->sockfd, cli, thread);


    // close the socket
    if (malloc_size(login_json))
        free(login_json);
    close(cli->sockfd);

    system("leaks -q client");

    return 0;
}
