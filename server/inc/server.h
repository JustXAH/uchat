//
// Created by Igor Khanenko on 12/22/20.
//

#ifndef UCHAT_MAIN_H
#define UCHAT_MAIN_H

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

#define MAX 4096
#define PORT 5000
#define MAX_CLIENTS 5

//struct for server
typedef struct s_server {
    sqlite3 *db;
    int *user_socket;
    int serv_sock_fd;
    int cli_connect;
    bool exit;

}              t_server;

//struct for database
typedef struct s_user {
    int id;
    char *login;
    char *password;
    struct s_user *next;
}              t_user;

typedef struct s_message {
    int id;
    int user;
    char *text;
    time_t timestamp;
    struct s_message *next;
} t_message;

/*
 * SERVER
 */
void mx_serv_struct_initialization(t_server *serv);
//cJSON *mx_database_stub(cJSON *user);
//void mx_read_server(t_server *serv);
void mx_check_read(t_server *serv, int i);
void mx_check_disconnect(t_server *server, int i);
void mx_login_and_pass_authentication(t_server *serv, char *u_login, char *u_pass, int user_sock);
void mx_user_registration(t_server *serv, char *u_login, char *u_pass, int user_sock);
void mx_user_search(t_server *serv, char *u_login, int user_sock);
void mx_add_new_contact(t_server *serv, int user_id, int contact_id, int user_sock);
void mx_add_new_chat(t_server *serv, int user_id, int contact_id, int user_sock);

/*
 * DATABASE
 */
sqlite3* mx_db_open(char *filename);
int mx_db_close(sqlite3 *db);
int mx_db_insert_new_user(sqlite3 *db, char *login, char *password); // return id of new user; 0 - login already exist
int mx_db_check_login(sqlite3 *db, char *login, char *password); //returns id; "0" - login doesn't exist; "-1" - wrong password
int mx_db_check_login_exist(sqlite3 *db, char *login); //returns id; "0" - login doesn't exist
int mx_db_init(sqlite3 *db); //clean db and init tables
int mx_db_create_new_contact(sqlite3 *db, int user, int contact); // return "-1" - if an error occurred while creating a new contact
int mx_db_create_new_chat(sqlite3 *db, int user, int contact); //return "-1" - if an error occurred while creating a new chat
int *mx_db_get_contacts(sqlite3 *db, int user); // 0-ended array of users_id; NULL if contactlist is empty
int *mx_db_get_chats(sqlite3 *db, int user);
//char *mx_db_get_login(sqlite3 *db, int user);
//int *mx_db_search_users_by_substr(sqlite3 *db, char *str); // 0-ended array of users_id; NULL if found nothing
//char **mx_db_search_logins_by_substr(sqlite3 *db, char *str);
//int mx_db_get_chat_by_users(sqlite3 *db, int user_1, int user_2); //return chat_id; 0 if chat doesn't exist
//int mx_db_create_new_message(sqlite3 *db, int user, int chat, char *text);
//t_message *mx_db_get_last_messages(sqlite3 *db, int chat);

#endif //UCHAT_MAIN_H
