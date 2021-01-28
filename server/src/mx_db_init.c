#include "server.h"

int mx_db_drop_init_fill(sqlite3 *db){
    char *err_msg = 0;
    int rc;

    char *sql = "DROP TABLE Users IF EXISTS;"
                "DROP TABLE Contacts IF EXISTS;"
                "DROP TABLE Chats IF EXISTS;"
                "DROP TABLE Messages IF EXISTS;"
                "DROP TABLE Files IF EXISTS;"
                "DROP TABLE Voices IF EXISTS;"
                "CREATE TABLE IF NOT EXISTS Users(Id INTEGER PRIMARY KEY, Login TEXT, Password TEXT, Picture INTEGER);"
                "CREATE TABLE IF NOT EXISTS Contacts(Id INTEGER PRIMARY KEY, User INTEGER, Contact INTEGER);"
                "CREATE TABLE IF NOT EXISTS Chats(Id INTEGER PRIMARY KEY, User INTEGER, User2 INTEGER, Notification INTEGER, Notification2);"
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

    mx_db_insert_new_user(db,"test","123456"); //1
    mx_db_insert_new_user(db,"max_z","password"); //2
    mx_db_insert_new_user(db,"max_b","onemoreline"); //3
    mx_db_insert_new_user(db,"ihor","123456"); //4
    mx_db_insert_new_user(db,"dima","carpathians"); //5
    mx_db_insert_new_user(db,"artem","qwerty123"); //6
    mx_db_create_new_contact(db,1,2); //1
    mx_db_create_new_contact(db,1,3); //2
    mx_db_create_new_contact(db,1,4); //3
    mx_db_create_new_contact(db,6,1); //4
    mx_db_create_new_contact(db,2,1);//5
    mx_db_create_new_contact(db,2,3);//6
    mx_db_create_new_contact(db,3,1);//7
    mx_db_create_new_contact(db,3,2);//8
    mx_db_create_new_contact(db,4,1);//9
    mx_db_create_new_contact(db,4,2);//10
    mx_db_create_new_contact(db,4,3);//11
    mx_db_create_new_contact(db,4,5);//12
    mx_db_create_new_chat(db,1,2);//1
    mx_db_create_new_chat(db,1,3);//2
    mx_db_create_new_chat(db,1,4);//3
    mx_db_create_new_chat(db,1,6);//4
    mx_db_create_new_chat(db,2,3);//5
    mx_db_create_new_chat(db,3,4);//6
    mx_db_create_new_chat(db,3,5);//7
    mx_db_create_new_chat(db,3,6);//8
    mx_db_create_new_chat(db,4,5);//9
    mx_db_create_new_chat(db,4,2);//10
    mx_db_create_new_chat(db,5,1);//11
    mx_db_create_new_message(db, 1, 4, "text0");
    mx_db_create_new_message(db, 1, 4, "text1");
    mx_db_create_new_message(db, 1, 4, "longlonglong longlong longtext2");
    mx_db_create_new_message(db, 6, 4, "text3");
    mx_db_create_new_message(db, 6, 4, "text4");
    mx_db_create_new_message(db, 1, 4, "text5");
    mx_db_create_new_message(db, 6, 4, "longlonglonglonglonglonglonglonglonglonglonglonglongtext6");
    mx_db_create_new_message(db, 1, 11, "test0");
    mx_db_create_new_message(db, 1, 11, "test1");
    mx_db_create_new_message(db, 5, 11, "longlonglong longlong longtest2");
    mx_db_create_new_message(db, 5, 11, "test3");
    mx_db_create_new_message(db, 5, 11, "test4");
    mx_db_create_new_message(db, 1, 11, "test5");
    mx_db_create_new_message(db, 1, 11, "longlonglonglonglonglonglonglonglonglonglonglonglongtest6");
    return 0;
}

int mx_db_init(sqlite3 *db) {
    char *err_msg = 0;
    int rc;

    char *sql = "CREATE TABLE IF NOT EXISTS Users(Id INTEGER PRIMARY KEY, Login TEXT, Password TEXT, Picture INTEGER);"
                "CREATE TABLE IF NOT EXISTS Contacts(Id INTEGER PRIMARY KEY, User INTEGER, Contact INTEGER);"
                "CREATE TABLE IF NOT EXISTS Chats(Id INTEGER PRIMARY KEY, User INTEGER, User2 INTEGER, Notification INTEGER, Notification2);"
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
