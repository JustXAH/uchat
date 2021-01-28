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
    t_system *sys = (t_system *)malloc(sizeof(t_system));
    t_user *user = (t_user *)malloc(sizeof(t_user));
    struct sockaddr_in servaddr;
    pthread_t thread_server;
//    int cli_socket = 0;

    chat = (t_chat *)malloc(sizeof(t_chat));
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
    printf("ARGC = %d\n", argc);
    printf("ARGV[1]= %s\n", argv[1]);
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

    printf("/nSOCKET = %d\n", sys->sockfd);

    mx_cache_dir_creator();

//    mx_login_or_register(sys, user);
//    pthread_mutex_init(&sys->mutex, NULL);

    chat->sys = sys;
    chat->user = user;
    chat->json = (t_json *)malloc(sizeof(t_json));
    // function for chat
    pthread_create(&thread_server, NULL, read_server, chat);

    //MB's shit (starting the client's listener function and initializing windows)//
    g_idle_add(mb_event_listener, NULL);
    gtk_window_initializtion(chat);
    printf("Waiting for finish thread read_server process...\n");

    sleep(4);

    cache_dir_removing();

    // read server thread closing
    while(chat->sys->exit != 1);
    pthread_cancel(thread_server);
    printf("Thread read_server closed.\n");

//    // close the socket
    printf("Socket closed.\n");
    //IDK why, but this seems to work
    sys->sockfd = -1;
    //close(chat->sys->sockfd);


    printf("GG WP!\n");

    system("leaks -q uchat");
    exit(0);
    return 0;
}

