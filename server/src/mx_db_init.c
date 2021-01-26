#include "server.h"

int mx_db_init(sqlite3 *db) {
    char *err_msg = 0;
    int rc;

    // char *sql = "DROP TABLE IF EXISTS Users;"
    //             "DROP TABLE IF EXISTS Contacts;"
    //             "DROP TABLE IF EXISTS Chats;"
    //             "DROP TABLE IF EXISTS Messages;"
    //             "DROP TABLE IF EXISTS Files;"
    //             "DROP TABLE IF EXISTS Voices;"
    //             "CREATE TABLE Users(Id INTEGER PRIMARY KEY, Login TEXT, Password TEXT);"
    //             "CREATE TABLE Contacts(Id INTEGER PRIMARY KEY, User INTEGER, Contact INTEGER);"
    //             "CREATE TABLE Chats(Id INTEGER PRIMARY KEY, User INTEGER, User2 INTEGER);"
    //             "CREATE TABLE Messages(Id INTEGER PRIMARY KEY, User INTEGER, Chat INTEGER, Text TEXT, Time INTEGER);"
    //             "CREATE TABLE Files(Id INTEGER PRIMARY KEY, Filename TEXT);"
    //             "CREATE TABLE Voices(Id INTEGER PRIMARY KEY, User INTEGER, Number INTEGER, FileId INTEGER)";
    char *sql = "CREATE TABLE IF NOT EXISTS Users(Id INTEGER PRIMARY KEY, Login TEXT, Password TEXT);"
                "CREATE TABLE IF NOT EXISTS Contacts(Id INTEGER PRIMARY KEY, User INTEGER, Contact INTEGER);"
                "CREATE TABLE IF NOT EXISTS Chats(Id INTEGER PRIMARY KEY, User INTEGER, User2 INTEGER);"
                "CREATE TABLE IF NOT EXISTS Messages(Id INTEGER PRIMARY KEY, User INTEGER, Chat INTEGER, Text TEXT, Time INTEGER);"
                "CREATE TABLE IF NOT EXISTS Files(Id INTEGER PRIMARY KEY, Filename TEXT);"
                "CREATE TABLE IF NOT EXISTS Voices(Id INTEGER PRIMARY KEY, User INTEGER, Number INTEGER, FileId INTEGER, VoiceName TEXT)";


    rc = sqlite3_exec(db, sql, 0, 0, &err_msg);

    if (rc != SQLITE_OK ) {
        fprintf(stderr, "Failed to create tables\n");
        fprintf(stderr, "SQL error: %s\n", err_msg);

    } else {
        fprintf(stdout, "Tables created successfully\n");
    }

    sqlite3_free(err_msg);
    return 0;
}
