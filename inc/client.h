//
// Created by Igor Khanenko on 12/22/20.
//

#ifndef UCHAT_CLIENT_H
#define UCHAT_CLIENT_H

#include "cJSON.h"
//#include "libmx.h"
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <unistd.h>
#include <errno.h>
#include <pthread.h>
#include <poll.h>

//frameworks/libraries
#include <sqlite3.h>
#include <gtk/gtk.h>
#include <glib.h>
#include <gio/gio.h>

//#define MAX 4096
//#define PORT 5000
//#define SA struct sockaddr

typedef struct s_client {
    char *login;
    char *password;
    char *reg_login;
    char *reg_password;
    char *reg_email;
    GtkBuilder *builder;

    GtkWindow *window;
    GtkWindow *reg_window;
    GtkWindow *chat_window;
    int sockfd;
////    pthread_mutex_t mutex;
    bool first_reg;
    bool authentication;
    bool registration;
}              t_client;
typedef struct s_reg_win {
    GtkEntry *log_entry;
    GtkEntry *pass_entry;
    GtkLabel *err_log_label;
    GtkLabel *err_pas_label;
    GtkStack *stk;
    GtkEntry *reg_log;
    GtkEntry *reg_pass1;
    GtkEntry *reg_pass2;
    GtkEntry *reg_email;
    GtkLabel *reg_log_label;
    GtkLabel *reg_pas_label1;
    GtkLabel *reg_pas_label2;
    GtkLabel *reg_email_label;
}               t_reg_win;
typedef struct s_chat_win {
    GtkEntry *chat_msg;
    GtkListBox *chat_viewer;
}                t_chat_win;
void reg_win_init(t_client *cli);
void chat_win_init(t_client *cli);
void mx_gtk_window(int argc, char **argv, t_client *cli);
void mx_struct_initialization(t_client *cli);
void gtk_chat_window(t_client *cli);
//void mx_login_or_register(t_client *cli);
//char *mx_create_user_profile(t_client *cli, bool registration);
//void mx_confirmation_of_registration(cJSON *SERVER_JSON, t_client *cli);
//void mx_authentication_client(cJSON *SERVER_JSON, t_client *cli);
//btn_log-cl

#endif //UCHAT_CLIENT_H
