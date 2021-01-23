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


// glade
#include <gtk/gtk.h>
#include <glib.h>
#include <gio/gio.h>

#define MAX_LEN 4096
#define PORT 5000
#define SA struct sockaddr

//enum for type cjson
typedef enum e_type_cJSON_message {
    AUTHENTICATION,
    REGISTRATION,
    USER_SEARCH_BY_SUBSTRING,
    USER_SEARCH_BY_LOGIN,
    NEW_CONTACT,
    NEW_CHAT,
    GET_LOGIN,
    LAST_MESSAGES,
}            e_type_cJSON;


typedef struct s_system {
//    char *login;
//    char *password;
//    int my_id;
    GtkBuilder *builder;
    GtkWindow *window;
    GtkWindow *reg_window;
    GtkWindow *chat_window;
    char **argv;
    char **found_usernames;
    char *found_username;
    int argc;
    int sockfd;
    int found_user_id;
    int found_usernames_count;
    e_type_cJSON type_enum;
//    pthread_mutex_t mutex;
    bool first_reg;
    bool reg_request;
    bool reg_confirmation;
    bool authentication;
    bool menu;
    bool message_sent;
    bool chat;
    bool exit;
}              t_system;

typedef struct s_user {
    char *login;
    char *password;
    int *contacts_id;
    char **contacts_login;
    int *chats_id;
    char **chats_name;
    int my_id;
    int contacts_count;
    int chats_count;
}              t_user;

typedef struct s_json {
    cJSON *SERVER_JSON;
    cJSON *SEND;
    cJSON *TYPE;
    cJSON *RESULT;
    cJSON *LOGIN;
    cJSON *PASS;
    cJSON *USER_ID;
    cJSON *CONTACT_ID;
    cJSON *CONTACTS_ID_ARR;
    cJSON *CONTACTS_COUNT;
    cJSON *CONTACTS_LOGIN_ARR;
    cJSON *CHATS_ID_ARR;
    cJSON *CHATS_COUNT;
    cJSON *CHATS_NAME_ARR;
    cJSON *FOUND_USERNAMES;
    cJSON *FOUND_LOGIN;
    cJSON *MESSAGE;
    cJSON *TO;
    cJSON *CHAT_ID;
}              t_json;

typedef struct s_chat {
    struct s_system *sys;
    struct s_user *user;
    struct s_json *json;
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
    GtkListBox *contact_list;
}                t_chat_win;

typedef struct s_client_st {
    char logged_in;  // 0 - not logged in // 1 - logged in // 2 - request for login sent
    char authentication;
    bool message_in_buffer;
    int contact_in_focus; // 0 - home page
    int logged_in_id;
    char *logged_in_name;
}               t_client_st;
/*
typedef struct s_msg {
    int user_id;
    char *user_name;
    char *msg_time;
    char *msg_text;
    bool outgoing;
    struct s_msg *next_msg;
}              t_msg;
*/
typedef struct s_message {
    int id;
    int user;
    char *user_name;
    char *text;
    bool outgoing;
    time_t timestamp;
    struct s_message *next;
}               t_message;

typedef struct s_contact_list {
    int user_id;
    char *user_name;
    t_message *chat_history;
    GtkWidget *contact_gui;
    struct s_contact_list *next_contact;
    //struct s_contact_list *prev_user;
}              t_contact_list;

void mx_structs_initialization(t_system *sys, t_user *user);
/*
 * READ SERVER ANSWER
 */
void *read_server(void *data); // second thread to read server responses
void mx_authentication_client(t_system *sys, t_user *user, t_json *json);
void mx_confirmation_of_registration(t_system *sys, t_user *user, t_json *json);
void mx_found_users_by_substr(t_system *sys, t_user *user, t_json *json);
void mx_found_user_by_login(t_system *sys, t_user *user, t_json *json);
void mx_add_new_contact(t_system *sys, t_user *user, t_json *json);
void mx_add_new_chat(t_system *sys, t_user *user, t_json *json);
void mx_get_login(t_system *sys, t_user *user, t_json *json);
/*
 * REQUEST TO SERVER
 */
void mx_add_new_contact_request(t_system *sys, t_user * user, t_json *json, int index);

void mx_login_or_register(t_system *sys, t_user *user);
char *mx_create_user_profile(t_system *sys, t_user *user);
void mx_account_login_request(t_system *sys, t_user *user);
void mx_registration_request(t_system *sys, t_user *user);
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
void gtk_window_initializtion(t_chat *chat);
void gtk_show_chat_window(t_chat *chat);
void gtk_show_log_window(t_chat *chat);

void reg_win_init(t_system *sys);
void chat_win_init(t_system *sys);
void mb_client_globals_initialization();

gboolean mb_event_listener(gpointer data);
void mb_auth_event_check();
void mb_incoming_msg_check();

void mb_contact_list_add(int user_id, char *user_name);
void mb_msg_buffer_add(int user_id, time_t time, char *msg_text);

void mb_send_msg(t_message *msg);
void mb_display_msg(t_message *msg);
void mb_display_chat_with_contact(int user_id);

void mb_invalid_credentials_msg();
void mb_reset_credentials_msg();

#endif //UCHAT_CLIENT_H
