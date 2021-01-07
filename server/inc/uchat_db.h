#include <sqlite3.h>

sqlite3* db_open(char *filename);
int db_close(sqlite3 *db);
int db_insert_new_user(sqlite3 *db, char *login, char *password);
int db_check_login(sqlite3 *db, char *login, char *password);
