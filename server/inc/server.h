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

/*
 * SERVER
 */
void mx_serv_struct_initialization(t_server *serv);
void mx_login_and_pass_authentication(t_server *serv, char *u_login, char *u_pass, int user_sock);
void mx_user_registration(t_server *serv, char *u_login, char *u_pass, int user_sock);
cJSON *mx_database_stub(cJSON *user);
void mx_read_server(t_server *serv);
void mx_check_read(t_server *serv, int i);
void mx_check_disconnect(t_server *server, int i);

/*
 * DATABASE
 */
sqlite3* mx_db_open(char *filename);
int mx_db_close(sqlite3 *db);
int mx_db_insert_new_user(sqlite3 *db, char *login, char *password); // return id of new user; 0 - login already exist
int mx_db_check_login(sqlite3 *db, char *login, char *password); //returns id; "0" - login doesn't exist; "-1" - wrong password
int mx_db_check_login_exist(sqlite3 *db, char *login); //returns id; "0" - login doesn't exist
int mx_db_init(sqlite3 *db); //clean db and init tables
int mx_db_create_new_contact(sqlite3 *db, int user, int contact); //
int mx_db_create_new_chat(sqlite3 *db, int user, int contact); //return chat_id
//int* mx_db_get_contacts(sqlite3 *db, int user) // 0-ended array of users_id

#endif //UCHAT_MAIN_H
