//
// Created by Igor Khanenko on 12/20/20.
//

#include "client.h"

extern t_reg_win reg__win;
//void *read_server(void *data) {
//    t_client *cli = (t_client *) data;
//    char buff[MAX];
//    cJSON *SERVER_JSON = NULL;
//    cJSON *TYPE = NULL;
//    cJSON *SENDER = NULL;
//    cJSON *MESSAGE = NULL;
//
////    char *str = NULL;
//
//    while (read(cli->sockfd, buff, sizeof(buff))) {
////        printf("%s\n", buff);
////        write(1, "\nFrom %", 6);
//        SERVER_JSON = cJSON_Parse(buff);
//        TYPE = cJSON_GetObjectItemCaseSensitive(SERVER_JSON, "TYPE");
//        if (TYPE != NULL) {
//            if (TYPE->valueint == 2) { //аутентификация
//                mx_authentication_client(SERVER_JSON, cli);
//            }
//            else if (TYPE->valueint == 3) { //подтверждение регистрации
//                mx_confirmation_of_registration(SERVER_JSON, cli);
//            }
//            else { //TYPE == 1 (сообщения)
////                pthread_mutex_lock(&cli->mutex);
//                SENDER = cJSON_GetObjectItemCaseSensitive(SERVER_JSON,
//                                                          "LOGIN");
//                MESSAGE = cJSON_GetObjectItemCaseSensitive(SERVER_JSON,
//                                                           "MESSAGE");
//                write (1, "\nFrom ", 6);
//                write(1, SENDER->valuestring, strlen(SENDER->valuestring));
//                write(1, ": ", 2);
//                write(1, MESSAGE->valuestring, strlen(MESSAGE->valuestring));
//                cJSON_DeleteItemFromObject(SERVER_JSON, "LOGIN");
////                pthread_mutex_unlock(&cli->mutex);
//            }
//            cJSON_DeleteItemFromObject(SERVER_JSON, "TYPE");
//            cJSON_DeleteItemFromObject(SERVER_JSON, "TO");
//            cJSON_DeleteItemFromObject(SERVER_JSON, "MESSAGE");
////        cJSON_free(MESSAGE);
//            memset(buff, '\0', sizeof(buff));
//        }
//        cJSON_Delete(SERVER_JSON);
//    }
//    return 0;
//}
//
//void func(int sockfd, t_client *cli, pthread_t thread) {
//    char buff[MAX];
//    char **split_str;
//    char *str_send;
//    cJSON *SEND = cJSON_CreateObject();
//    cJSON *TYPE = cJSON_CreateNumber(1);
//    cJSON *LOGIN = cJSON_CreateString(cli->login);
//    cJSON *TO = NULL;
//    cJSON *MESSAGE = NULL;
////    int n = 0;
//
////    bool first_entry = true;
////    if (cli->authentication == true) {
//        for (;;) {
//            if (cli->authentication == true) {
////                sleep(1);
//                usleep(200);
//                //остановка потока read_server, на момент ввода сообщения юзером
////                pthread_mutex_lock(&cli->mutex);
//                write(1, "\n\nEnter your message: ", 22);
//
//                scanf("%s", buff);
//
//                //восстановление потока read_server, после ввода сообщения юзером
////                pthread_mutex_unlock(&cli->mutex);
//
////        while ((buff[n++] = getchar()) != '\n');
////        n = 0;
//                if ((strncmp(buff, "exit", 4)) == 0) {
//                    write(1, "Client Exit\n", 12);
//                    pthread_cancel(thread);
//                    break;
//                } else {
//                    split_str = mx_strsplit(buff, ';');
//                    if (split_str[1] == NULL)
//                        write(1,
//                              "\nERROR, invalid  struct of message.\nusage: [message][;][socket]",
//                              64);
//                    else {
//                        mx_del_char(split_str[1], mx_strlen(split_str[1]) - 1,
//                                    '\n');
//                        MESSAGE = cJSON_CreateString(split_str[0]);
//                        TO = cJSON_CreateNumber(mx_atoi(split_str[1]));
//                        cJSON_AddItemToObject(SEND, "TYPE", TYPE);
//                        cJSON_AddItemToObject(SEND, "LOGIN", LOGIN);
//                        cJSON_AddItemToObject(SEND, "MESSAGE", MESSAGE);
//                        cJSON_AddItemToObject(SEND, "TO", TO);
//                        str_send = cJSON_Print(SEND);
////                printf("\n\nJSON send to server:%s\n\n", str_send);
//                        write(sockfd, str_send, strlen(str_send));
//                        cJSON_DeleteItemFromObject(SEND, "MESSAGE");
//                        cJSON_DeleteItemFromObject(SEND, "TO");
//                        if (malloc_size(str_send))
//                            free(str_send);
//                    }
//                    mx_del_strarr(&split_str);
//                    memset(buff, '\0', sizeof(buff));
//                }
//            }
//        }
//        cJSON_Delete(SEND);
//}


int main(int argc, char *argv[]) {
    t_client *cli = (t_client *)malloc(sizeof(t_client));
//    struct sockaddr_in servaddr;
//    pthread_t thread;
    mx_struct_initialization(cli);


    mx_gtk_window(argc, argv, cli);


    printf("\nLOGIN = %s\nPASS = %s\n", cli->login, cli->password);

//    // socket create and varification
//    cli->sockfd = socket(AF_INET, SOCK_STREAM, 0);
//    if (cli->sockfd == -1) {
//        write(2, "ERROR, socket creation failed\n", 30);
//        exit(0);
//    }
//    else
//        write(1, "Socket successfully created...\n", 31);
//    bzero(&servaddr, sizeof(servaddr));
//
//    // assign IP, PORT
//    servaddr.sin_family = AF_INET;
//    if (argc == 2) {
//        servaddr.sin_addr.s_addr = inet_addr(argv[1]);
//    }
//    else {
//        servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
//    }
//    servaddr.sin_port = htons(PORT);
//
//    // connect the client socket to server socket
//    if (connect(cli->sockfd, (SA*)&servaddr, sizeof(servaddr)) != 0) {
//        write(2, "ERROR, connection with the server failed!\n", 42);
//        exit(0);
//    }
//    else
//        write(1, "Successfully connected to the server...\n\n", 41);
//
//    mx_login_or_register(cli);
////    pthread_mutex_init(&cli->mutex, NULL);
//
//    // function for chat
//    pthread_create(&thread, NULL, read_server, cli);
//    func(cli->sockfd, cli, thread);
//
//
//    // close the socket
//    close(cli->sockfd);
//
//    system("leaks -q client");

    return 0;
}
