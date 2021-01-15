//
// Created by Igor Khanenko on 12/22/20.
//

#ifndef UCHAT_CLIENT_H
#define UCHAT_CLIENT_H


#ifdef __APPLE__
#define MALLOC_SIZE malloc_size
#elif __linux__
#define _XOPEN_SOURCE 500 
#define MALLOC_SIZE malloc_usable_size
#include <strings.h>
#endif

#include "cJSON.h"
#include "libmx.h"
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <pthread.h>
#include <poll.h>
#include <ctype.h>
#include <unistd.h>
#include <string.h>

// glade
#include <gtk/gtk.h>
#include <glib.h>
#include <gio/gio.h>

#define MAX_LEN 4096
#define PORT 5000
#define SA struct sockaddr


typedef struct s_system {
//    char *login;
//    char *password;
//    int my_id;
    char **argv;
    int argc;
    GtkBuilder *builder;
    GtkWindow *window;
    GtkWindow *reg_window;
    GtkWindow *chat_window;
    int sockfd;
//    pthread_mutex_t mutex;
    bool first_reg;
    bool registration;
    bool authentication;
    bool menu;
    bool message_sent;
    bool chat;
    bool exit;
}              t_system;

typedef struct s_user {
    char *login;
    char *password;
    int *contacts;
    int *chats;
    int my_id;
}              t_user;

typedef struct s_chat {
    struct s_system *sys;
    struct s_user *user;
}              t_chat;

//structs for glade
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

typedef struct s_client_st {
    bool logged_in;
    bool authentication;
    bool message_in_buffer;

}               t_client_st;

void mx_structs_initialization(t_system *sys, t_user *user);
void mx_login_or_register(t_system *sys, t_user *user);
char *mx_create_user_profile(t_system *sys, t_user *user);
void mx_account_login_request(t_system *sys, t_user *user);
void mx_registration_request(t_system *sys, t_user *user);
void mx_confirmation_of_registration(t_system *sys, t_user *user, cJSON *SERVER_JSON);
void mx_authentication_client(t_system *sys, t_user *user, cJSON *SERVER_JSON);
void mx_chat_event(t_system *sys, t_user *user, pthread_t thread);
void mx_client_menu(t_system *sys, t_user *user);
void mx_sending_messages(t_system *sys, t_user *user, char *buff); // нужно переделать сначала сервер-бд, потом здесь

void mx_registration_or_login_request(t_system *sys, t_user *user);

/*
 * MENU
 */
void mx_view_contacts_list(t_system *sys, t_user *user);
void mx_view_chats_list(t_system *sys, t_user *user);
void mx_user_search(t_system *sys, t_user *user);

/*
 * GLADE
 */
void client_st_init();
void reg_win_init(t_system *sys);
void chat_win_init(t_system *sys);
void gtk_log_window(t_chat *chat);
void gtk_chat_window(t_chat *chat);
void mb_display_messge(char *msg_text);

#endif //UCHAT_CLIENT_H
