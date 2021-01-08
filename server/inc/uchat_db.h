#include <sqlite3.h>
#include "libmx.h"

sqlite3* db_open(char *filename);
int db_close(sqlite3 *db);
int db_insert_new_user(sqlite3 *db, char *login, char *password);
int db_check_login(sqlite3 *db, char *login, char *password); //returns id; "0" - login doesn't exist; "-1" - wrong password


typedef struct s_user {
    int id;
    char *login;
    char *password;
    struct s_user *next;
} s_user;
