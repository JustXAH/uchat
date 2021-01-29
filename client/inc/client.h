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
#include <sys/stat.h>
#include <gdk-pixbuf/gdk-pixbuf.h>

// glade
#include <gtk/gtk.h>
#include <glib.h>
#include <gio/gio.h>

#define MAX_LEN 1024
#define SA struct sockaddr
#define NUMBER_VOICES 8


//enum for type cjson
typedef enum e_type_cJSON_message {
    AUTHENTICATION,
    REGISTRATION,
    WHO_ONLINE,
    USER_SEARCH_BY_SUBSTRING,
    USER_SEARCH_BY_LOGIN,
    NEW_CONTACT,
    NEW_CHAT,
    GET_LOGIN,
    NEW_MESSAGE,
    HISTORY_CHAT,
    NEW_VOICE,
    SEND_VOICE_TO_USER,
    NEW_USER_PIC,
    REMOVE_NOTIFICATION,
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
    char *login_substr;
    char *searched_login;
    char *found_user_login;
    char *file_path;
    char *filename;
    char *voice_name;
    int position;
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
    bool voice_play;
    char exit;
}              t_system;
typedef struct s_user {
    char *login;
    char *password;
    char *hash_password;
    int *contacts_id;
    char **contacts_login;
    int *chats_id;
    char **chats_name;
    int *who_online; // users with online status
    char **voices_name;
    int *voices_id;
    int who_online_count;
    int my_id;
    int contacts_count;
    int chats_count;
    int user_pic_id;
    int *notification;
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
    cJSON *WHO_ONLINE;
    cJSON *CHATS_ID_ARR;
    cJSON *CHATS_COUNT;
    cJSON *CHATS_NAME_ARR;
    cJSON *LOGIN_SUBSTR;
    cJSON *SEARCHED_LOGIN;
    cJSON *FOUND_USERNAMES;
    cJSON *FOUND_USER_ID;
    cJSON *FOUND_LOGIN;
    cJSON *MESSAGE;
    cJSON *TO;
    cJSON *CHAT_ID;
    cJSON *MESSAGES_ARR;
    cJSON *COUNT_MESSAGES_ARR;
    cJSON *MESSAGES_ID;
    cJSON *MESSAGES_TIME;
    cJSON *SENDER_ID;
    cJSON *FILENAME;
    cJSON *POSITION;
    cJSON *VOICE_ID;
    cJSON *VOICE_NAME;
    cJSON *USER_NAME;
    cJSON *MESSAGE_ID;
    cJSON *MESSAGE_TIME;
    cJSON *CONTACT_NAME;
    cJSON *VOICES_ID_ARR;
    cJSON *VOICES_NAME_ARR;
    cJSON *USER_PIC_ID;
    cJSON *DISPATCH;
    cJSON *NOTIFICATION;
    cJSON *FILE_SIZE;
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
    GtkStackSwitcher       *switcher;
    //GtkStackSwitcher *contacts_bar;
    //GtkStackSwitcher *chats_bar;

    GtkListBox        *contacts_list;
    GtkListBox           *chats_list;
    GtkListBox          *search_list;
    
    GtkStack           *search_stack;
    GtkStack              *all_stack;
    GtkFixed         *my_profile_box;
    GtkFixed          *u_profile_box;
    GtkBox         *edit_vax_box;

    GtkFixed         *edit_profile;
    GtkLabel        *err_msg_lbl;

    GtkDialog       *err_pop;

    GtkBox                  *msg_box;
    GtkStack          *msg_entry_stk;
    GtkBox             *msg_entry_box;
    GtkBox             *vox_entry_box;

    GtkEntry              *msg_entry;
    GtkListBox           *msg_viewer;

    GtkSearchEntry     *csearch_entry;
    GtkSearchEntry     *fsearch_entry;
    GtkWidget              **fresults;
    GtkWidget              *file_choose_window;

    GtkLabel            *welcome_user;

    GtkLabel            *friend_login;
    GtkScrolledWindow  *scrl_chat_box;

    GtkEntry     *edit_vax1_entry;
    GtkEntry     *edit_vax2_entry;
    GtkEntry     *edit_vax3_entry;
    GtkEntry     *edit_vax4_entry;
    GtkEntry     *edit_vax5_entry;
    GtkEntry     *edit_vax6_entry;
    GtkEntry     *edit_vax7_entry;
    GtkEntry     *edit_vax8_entry;
    GtkButton  *Vox_1;
    GtkButton  *Vox_2;
    GtkButton  *Vox_3;
    GtkButton  *Vox_4;
    GtkButton  *Vox_5;
    GtkButton  *Vox_6;
    GtkButton  *Vox_7;
    GtkButton  *Vox_8;

    GtkStack *add_remove_stk;
    GtkButton *add_user;
    GtkButton *remove_user;
    GtkImage *edit_avatar_img;
    GtkImage *profile_avatar_img;
    GtkLabel *profile_login;
}                t_chat_win;

typedef struct s_client_st {
    char logged_in;  // 0 - not logged in // 1 - logged in // 2 - request for login sent
    char authentication;
    bool message_in_buffer;
    int chat_in_focus; // 0 - home page
    int user_in_focus;
    int my_id;
    char *my_name;
    bool fsearch;
    bool *pending_requests;
    bool just_added_new_friend;
    bool new_contact_received;
    bool vox_not_msg;
    int requested_user_id;
    char *requested_user_name;
    bool dont_bother_search;
}               t_client_st;

typedef struct s_message {
    //int id;
    int user_id;
    int chat_id;
    int msg_id;
    char *user_name;
    char *text;
    bool outgoing;

    char *timestamp;
    struct s_message *next;
}               t_message;

typedef struct s_chat_list {
    int user_id;
    char *user_name;
    int user_amount;
    bool is_online;
    GtkWidget *contact_gui;
    struct s_chat_list *next_chat;
}              t_chat_list;
/*typedef struct s_contact_list {
    
}              t_contact_list;*/

/*
 * MAIN
 */
void mx_structs_initialization(t_system *sys, t_user *user);
void mx_cache_dir_creator();

/*
 * READ SERVER ANSWER
 */
void *read_server(void *data); // second thread to read server responses
void mx_authentication_client(t_system *sys, t_user *user, t_json *json);
void mx_confirmation_of_registration(t_system *sys, t_user *user,
                                     t_json *json);
void mx_who_online_update(t_system *sys, t_user *user, t_json *json);
void mx_found_users_by_substr(t_system *sys, t_user *user, t_json *json);
void mx_found_user_by_login(t_system *sys, t_user *user, t_json *json);
void mx_add_new_contact(t_system *sys, t_user *user, t_json *json);
void mx_add_new_chat(t_system *sys, t_user *user, t_json *json);
void mx_get_login(t_system *sys, t_user *user, t_json *json);
void mx_get_history_chat(t_system *sys, t_user *user, t_json *json);
void mx_add_new_message(t_system *sys, t_user *user, t_json *json);
void mx_get_voice_file_from_user(t_system *sys, t_user *user, t_json *json);
void mx_get_voice_file_id(t_system *sys, t_user *user, t_json *json);
char *mx_file_receiving(t_system *sys, char *filename, int file_size);
void mx_get_user_pic_id(t_system *sys, t_user *user, t_json *json);
int mx_file_size_measurement(char *file_path);



/*
 * REQUEST TO SERVER
 */
void mx_registration_or_login_request(t_system *sys, t_user *user,
                                      t_json *json);
void mx_user_search_by_substr_request(t_system *sys, t_json *json);
void mx_user_search_by_login_request(t_system *sys, t_json *json);
void mx_add_new_contact_request(t_system *sys, t_user * user, t_json *json, int contact_id);
void mx_add_new_chat_request(t_system *sys, t_user * user, t_json *json, int contact_id);
void mx_add_message_request(t_system *sys, t_user *user, t_json *json, char *messages_str, int chat_id, int contact_id);
void mx_get_history_chat_request(t_system *sys, t_user *user, t_json *json, int chat_id);
void mx_save_voice_file_request(t_system *sys, t_user *user, t_json *json);
void mx_send_voice_file_to_user_request(t_system *sys, t_json *json,
                                        int voice_id, int contact_id);
void mx_save_user_pic_file_request(t_system *sys, t_user *user, t_json *json);
void mx_send_file_to_server(t_system *sys, char *file_path);
int mx_file_size_measurement(char *file_path);
void mx_remove_notification_request(t_system *sys, t_json *json, t_user *user, int chat_id, int user_id);
bool mx_checking_friend_status(t_user *user, int contact_id);

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
void mb_new_contact_check();

void mb_contact_list_add(int user_id, char *user_name, bool is_online);
void mb_msg_buffer_add(int msg_id, int chat_id, int user_id, char *user_name, char *time, char *msg_text, bool outgoing);

//void mb_send_msg(t_message *msg);
void mb_display_msg(t_message *msg);
void mb_display_chat_with_contact(int chat_id);
//void mb_add_msg_to_history(t_message **history, t_message *new_msg);

void mb_invalid_credentials_msg();
void mb_reset_credentials_msg();

//int mb_get_uid_by_cid(int chat_id);

gboolean on_search_entry_match_select(GtkEntryCompletion *widget,
                                        GtkTreeModel       *model,
                                        GtkTreeIter        *iter,
                                        gpointer            user_data);
#endif //UCHAT_CLIENT_H
