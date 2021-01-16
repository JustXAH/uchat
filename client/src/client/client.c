//
// Created by Igor Khanenko on 12/20/20.
//

#include "client.h"

extern t_reg_win reg__win;

void *listen_signal(void *data) {
    t_chat *chat = (t_chat *) data;
    t_system *sys = chat->sys;
    t_user *user = chat->user;

//    write(1, "1\n", 2);
//    gtk_main();
//    write(1, "2\n", 2);
//    while (check == true) {
//        write(1, "Potok RABOTAET\n", 15);
////        check = false;
//    }
}

//void *read_server(void *data) {
//    t_chat *chat = (t_chat *)data;
//    t_system *sys = chat->sys;
//    t_user *user = chat->user;
//    char buff[MAX_LEN];
//    cJSON *SERVER_JSON = NULL;
//    cJSON *TYPE = NULL;
//    cJSON *SENDER = NULL;
//    cJSON *MESSAGE = NULL;
//
////    char *str = NULL;
////    write(1, "\nSOCKET =", 9);
////    write(1, mx_itoa(chat->sys->sockfd), 1);
////    printf("/nSocket = %d", chat->sys->sockfd);
//    while (read(sys->sockfd, buff, sizeof(buff))) {
////        printf("%s\n", buff);
////        write(1, "\nFrom %", 6);
//        SERVER_JSON = cJSON_Parse(buff);
//        TYPE = cJSON_GetObjectItemCaseSensitive(SERVER_JSON, "TYPE");
//        if (TYPE != NULL) {
//            if (TYPE->valueint == 2) { //аутентификация
//                mx_authentication_client(sys, user, SERVER_JSON);
//            }
//            else if (TYPE->valueint == 3) { //подтверждение регистрации
//                mx_confirmation_of_registration(sys, user, SERVER_JSON);
//                if (sys->registration == true) {
//                    mx_account_login_request(sys, user);
//                }
//            }
//            else { //TYPE == 1 (сообщения)
////                pthread_mutex_lock(&sys->mutex);
//                SENDER = cJSON_GetObjectItemCaseSensitive(SERVER_JSON,
//                                                          "LOGIN");
//                MESSAGE = cJSON_GetObjectItemCaseSensitive(SERVER_JSON,
//                                                           "MESSAGE");
//                write (1, "\nFrom ", 6);
//                write(1, SENDER->valuestring, strlen(SENDER->valuestring));
//                write(1, ": ", 2);
//                write(1, MESSAGE->valuestring, strlen(MESSAGE->valuestring));
//                cJSON_DeleteItemFromObject(SERVER_JSON, "LOGIN");
////                pthread_mutex_unlock(&sys->mutex);
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



int main(int argc, char *argv[]) {
    t_system *sys = (t_system *)malloc(sizeof(t_system));
    t_user *user = (t_user *)malloc(sizeof(t_user));
    t_chat *chat = (t_chat *)malloc(sizeof(t_chat));
    struct sockaddr_in servaddr;
    pthread_t thread_server;
    pthread_t thread_signal;

    mx_structs_initialization(sys, user);

//    printf("\nLOGIN = %s\nPASS = %s\n", user->login, user->password);

    // socket create and varification
    sys->sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sys->sockfd == -1) {
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
    if (connect(sys->sockfd, (SA*)&servaddr, sizeof(servaddr)) != 0) {
        write(2, "ERROR, connection with the server failed!\n", 42);
        exit(0);
    }
    else
        write(1, "Successfully connected to the server...\n\n", 41);

    printf("/nSocket = %d\n2", sys->sockfd);

//    mx_login_or_register(sys, user);
//    pthread_mutex_init(&sys->mutex, NULL);

    chat->sys = sys;
    chat->user = user;
    // function for chat
    pthread_create(&thread_signal, NULL, listen_signal, chat);
    pthread_create(&thread_server, NULL, read_server, chat);

    mx_gtk_window(sys, user);
//    mx_chat_event(sys, user, thread_server);

    mx_
    // close the socket
    close(sys->sockfd);

    system("leaks -q client");

    return 0;
}
