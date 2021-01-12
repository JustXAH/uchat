#pragma once

//sys
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>
#include <ctype.h>
#include <stdbool.h>
//sys

//frameworks/libraries
#include <sqlite3.h>
#include <gtk/gtk.h>
#include <glib.h>
#include <gio/gio.h>
// #include "../../libraries/include/cJSON.h"
//frameworks/libraries

// //struct
// typedef struct s_chat {
//     int sockfd;
//     char *con_ip;
//     int con_port;
//     char *username;
//     GtkWidget *window;
//     GtkBuilder *builder;
// }              t_chat;
// //struct

// //autorization
// void mx_register_request(t_chat *chat);
// void mx_login_request(t_chat *chat);
// void mx_login_handl_res(cJSON *j_responce, t_chat *chat);
// void autorized_accept(t_chat *chat);
// void autorized_decline(t_chat *chat, char flag);
// void mx_send_logout(t_chat *chat);
// //autorization

// //gui
// int mx_valid_login_gui(t_chat *chat);
// void mx_create_window(t_chat *chat);
// void mx_init_gui(t_chat *chat);
// void destroy(t_chat *chat);
// void mx_close_client(cJSON *j_responce, t_chat *chat);
// void mx_valid_csearch(t_chat *chat);
// void mx_create_contact(t_chat *chat, char *login);
// void mx_addcont_handl_res(cJSON *j_responce, t_chat *chat);
// //gui

// //client
// void mx_valid_argv(int argc, char **argv, t_chat *chat);
// void mx_start_chat(t_chat *chat);
// void quit_chat(t_chat *chat);
// //client

// //connection
// int mx_create_conn(t_chat *chat);
// void *mx_client_recv(void *data);
// //connection

// //json
// void mx_cjson_parser(char recvBuff[1024], t_chat *chat);
//json