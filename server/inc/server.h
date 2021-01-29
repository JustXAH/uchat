//
// Created by Igor Khanenko on 12/22/20.
//

#ifndef UCHAT_MAIN_H
#define UCHAT_MAIN_H

#ifdef __APPLE__
#define MALLOC_SIZE malloc_size
#elif __linux__
#define _XOPEN_SOURCE 500
#define MALLOC_SIZE malloc_usable_size
#include <strings.h>
#endif

#include "cJSON.h"
#include "libmx.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <poll.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <pthread.h>
#include <time.h>
#include <sqlite3.h>
#include <sys/stat.h>

#define MAX_LEN 1024
#define MAX_USERS 128
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

//struct for server
typedef struct s_server {
    sqlite3 *db;
    int *user_socket;
    int *users_id;
    time_t *last_voice_send;
    int serv_sock_fd;
    int cli_connect;
    bool update;
    bool exit;
    e_type_cJSON type_enum;
}              t_server;

typedef struct s_json {
    cJSON *USER_JSON;
    cJSON *SEND;
    cJSON *TYPE;
    cJSON *RESULT;
    cJSON *LOGIN;
    cJSON *PASS;
    cJSON *USER_ID;
    cJSON *CONTACT_ID;
    cJSON *CONTACTS_ID_ARR;
    cJSON *CONTACTS_LOGIN_ARR;
    cJSON *CONTACTS_COUNT;
    cJSON *CHATS_ID_ARR;
    cJSON *CHATS_NAME_ARR;
    cJSON *CHATS_COUNT;
    cJSON *LOGIN_SUBSTR;
    cJSON *SEARCHED_LOGIN;
    cJSON *FOUND_USERNAMES;
    cJSON *FOUND_USER_ID;
    cJSON *FOUND_LOGIN;
    cJSON *MESSAGE;
    cJSON *MESSAGES_ARR;
    cJSON *CHAT_ID;
    cJSON *COUNT_MESSAGES_ARR;
    cJSON *SENDER_ID;
    cJSON *MESSAGES_TIME;
    cJSON *MESSAGES_ID;
    cJSON *FILENAME;
    cJSON *POSITION;
    cJSON *VOICE_ID;
    cJSON *VOICE_NAME;
    cJSON *USER_NAME;
    cJSON *MESSAGE_TIME;
    cJSON *MESSAGE_ID;
    cJSON *VOICES_ID_ARR;
    cJSON *VOICES_NAME_ARR;
    cJSON *USER_PIC_ID;
    cJSON *DISPATCH;
    cJSON *NOTIFICATION;
    cJSON *FILE_SIZE;
}              t_json;

typedef struct s_user {
    int id;
    char *login;
    char *password;
    int photo_file_id;
    struct s_user *next;
}              t_user;

typedef struct s_contact {
    int *id;
    char **login;
    int count;
}              t_contact;

typedef struct s_chat {
    int *id;
    char **chat_name;
    int *notification;
    time_t *timestamp;
    int count;
}              t_chat;

typedef struct s_user_info {
    int id;
    char *login;
    int photo_file_id;
}              t_user_info;

typedef struct s_chat_info {
    int id;
    char *chat_name;
    int notification;
    time_t timestamp;
    struct s_chat_info *next;
}               t_chat_info;

typedef struct s_message_info {
    int id;
    int user;
    char *text;
    time_t timestamp;
    struct s_message_info *next;
}               t_message_info;

typedef struct s_message {
    int *id;
    int *user;
    char **text;
    time_t *timestamp;
    int count;
}               t_message;

typedef struct s_voice {
    int *id;
    char **filename;
    char **voice_name;
}               t_voice;


/*
 * SERVER
 */
void mx_serv_struct_initialization(t_server *serv);
void mx_media_dirs_creator();
void mx_json_struct_initialization(t_json *json);
void mx_sorting_users_and_sockets(t_server *serv);
void mx_update_handler(t_server *serv);
void mx_sending_who_online(t_server *serv, int user_index);
void mx_check_read(t_server *serv, int user_index);
void mx_check_disconnect(t_server *serv, int user_index);
void mx_login_and_pass_authentication(t_server *serv, t_json *json, int user_index);
void mx_user_registration(t_server *serv, t_json *json, int user_index);
void mx_user_search_by_substr(t_server *serv, t_json *json, int user_index);
void mx_user_search_by_login(t_server *serv, t_json *json, int user_index);
void mx_add_new_contact(t_server *serv, t_json *json, int user_index);
void mx_add_new_chat(t_server *serv, t_json *json, int user_index);
void mx_add_new_message(t_server *serv, t_json *json, int user_index);
void mx_get_login(t_server *serv, t_json *json, int user_index);
void mx_history_chat(t_server *serv, t_json *json, int user_index);
void mx_remove_notification(t_server *serv, t_json *json);
void mx_save_voice_file_and_get_id(t_server *serv, t_json *json, int user_index);
void mx_voice_file_receiver(t_server *serv, char *unique_name, int file_size,
                            int user_index);
void mx_send_voice_file_handler(t_server *serv, t_json *json, int user_index);
void mx_send_voice_file_to_user(t_server *serv, char *file_path,
                                int user_socket);
void mx_save_user_pic_and_get_id(t_server *serv, t_json *json,
                                 int user_index);
void mx_user_pic_receiver(t_server *serv, char *unique_name, int file_size,
                          int user_index);
void mx_send_user_pic_to_user(char *file_path, int user_socket);
int mx_file_size_measurement(char *file_path);
char *mx_get_file_path(char *path_to_dir, char *filename);


/*
 * DATABASE
 */

sqlite3* mx_db_open(char *filename);
int mx_db_close(sqlite3 *db);
int mx_db_insert_new_user(sqlite3 *db, char *login, char *password); // return id of new user; 0 - login already exist
int mx_db_check_login(sqlite3 *db, char *login, char *password); //returns id; "0" - login doesn't exist; "-1" - wrong password
int mx_db_check_login_exist(sqlite3 *db, char *login); //returns id; "0" - login doesn't exist
int mx_db_change_login(sqlite3* db, int user, char* new_login); //return 1 - login already taken, 0 - success
int mx_db_change_password(sqlite3* db, int user, char* new_password); // 0 - success
int mx_db_init(sqlite3 *db); //clean db and init tables
int mx_db_drop_init_fill(sqlite3 *db); //clean db and init tables
int mx_db_create_new_contact(sqlite3 *db, int user, int contact); //
int mx_db_delete_contact(sqlite3 *db, int user, int contact);
int mx_db_set_user_picture(sqlite3 *db, int user, char *filename); //
int mx_db_change_picture(sqlite3 *db, int user, char *filename); //
int mx_db_create_new_chat(sqlite3 *db, int user, int contact); //return chat_id
int mx_db_delete_chat(sqlite3 *db, int chat);
int *mx_db_get_contacts(sqlite3 *db, int user); // 0-ended array of users_id; NULL if contact list is empty
t_contact *mx_db_get_contacts_info(sqlite3 *db, int user); //
int *mx_db_get_chats(sqlite3 *db, int user);
char *mx_db_get_login(sqlite3 *db, int user);
t_user_info *mx_db_get_user(sqlite3 *db, int user);
int *mx_db_search_users_by_substr(sqlite3 *db, char *str); // 0-ended array of users_id; NULL if found nothing
char **mx_db_search_logins_by_substr(sqlite3 *db, char *str);
int mx_db_get_chat_by_users(sqlite3 *db, int user_1, int user_2); //return chat_id; 0 if chat doesn't exist
t_chat *mx_db_get_chats_info(sqlite3 *db, int user);
int mx_db_create_new_message(sqlite3 *db, int user, int chat, char *text);
t_message *mx_db_get_last_messages(sqlite3 *db, int chat);
t_message_info *mx_db_get_message(sqlite3 *db, int mes_id);
int mx_db_clear_history(sqlite3 *db, int chat);

int mx_db_insert_new_file(sqlite3 *db, char *filename);
int mx_db_insert_new_voice(sqlite3 *db, int user, int number, char *filename, char *voice_name);
t_voice *mx_db_get_users_voices(sqlite3 *db, int user);
char* mx_db_get_filename(sqlite3 *db, int id);

//int mx_db_get_notification(sqlite3 *db, int chat_id, int user_id);
int mx_db_clear_notification(sqlite3 *db, int chat_id, int user_id);

#endif //UCHAT_MAIN_H
