//
// Created by Igor Khanenko on 12/20/20.
//

#include "client.h"

t_chat *chat;
extern t_reg_win reg__win;
extern t_client_st cl_listener;
extern t_message *incoming_msg_buffer;

static void cache_dir_removing() {
    struct stat st = {0};

    if (stat("client/cache", &st) == 0) {
        // removing cache folder
        if (rmdir("client/cache") == 0) {
            printf("Successfully removed cache directory.\n");
        }
        else {
            printf("ERROR deleting the cache folder!\n");
        }
    }
}

int main(int argc, char *argv[]) {
    t_system *sys = NULL;
    t_user *user = NULL;
    struct sockaddr_in servaddr;
    pthread_t thread_server;

    if (argc != 3) {
        mx_printerr("usage: ./uchat_server [server IP address] [network port]\n");
        exit(1);
    }

    sys = (t_system *)malloc(sizeof(t_system));
    user = (t_user *)malloc(sizeof(t_user));
    chat = (t_chat *)malloc(sizeof(t_chat));
    mx_structs_initialization(sys, user);

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
    servaddr.sin_addr.s_addr = inet_addr(argv[1]);
    servaddr.sin_port = htons((__uint16_t)atoi((const char *)argv[2]));

    // connect the client socket to server socket
    if (connect(sys->sockfd, (SA*)&servaddr, sizeof(servaddr)) != 0) {
        write(2, "ERROR, connection with the server failed!\n", 42);
        exit(0);
    }
    else
        write(1, "Successfully connected to the server...\n\n", 41);

    mx_cache_dir_creator();

    chat->sys = sys;
    chat->user = user;
    chat->json = (t_json *)malloc(sizeof(t_json));
    // function for chat
    pthread_create(&thread_server, NULL, read_server, chat);

    //MB's shit (starting the client's listener function and initializing windows)//
    g_idle_add(mb_event_listener, NULL);
    gtk_window_initializtion(chat);
    printf("Waiting for read_server thread  to shut down...\n");

    //sleep(4);

    cache_dir_removing();

    // read server thread closing
    while(chat->sys->exit != 1);
    pthread_cancel(thread_server);
    printf("Thread read_server closed.\n");

//    // close the socket
    printf("Socket closed.\n");

    sys->sockfd = -1;

    printf("GG WP!\n");

//    system("leaks -q uchat");
    return 0;
}

