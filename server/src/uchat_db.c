#include <stdio.h>
#include <uchat_db.h>

sqlite3* db_open(char *filename) {
    sqlite3 *db;
    sqlite3_stmt *res;

    int rc = sqlite3_open(filename, &db);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return NULL;
    }

    rc = sqlite3_prepare_v2(db, "SELECT SQLITE_VERSION()", -1, &res, 0);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to fetch data: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return NULL;
    }

    rc = sqlite3_step(res);
    if (rc == SQLITE_ROW) {
        printf("ver = %s\n", sqlite3_column_text(res, 0));
    }

    sqlite3_finalize(res);
    return db;
}


int db_close(sqlite3 *db){
    sqlite3_close(db);
    return 0;
}

// int db_init(sqlite3 *db) {
// "CREATE TABLE Users(Id INTEGER PRIMARY KEY, Login TEXT, Password TEXT);"
// }

int db_insert_new_user(sqlite3 *db, char *login, char *password) {
    char *err_msg = 0;
    int rc;

    char sql[1024];
    snprintf(sql, sizeof(sql),
        "INSERT INTO Users(Login,Password) VALUES ('%s','%s');",login,password);

    rc = sqlite3_exec(db, sql, 0, 0, &err_msg);

    if (rc != SQLITE_OK ) {
        fprintf(stderr, "Failed to create table\n");
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
    } else {
        fprintf(stdout, "Table Users created successfully\n");
    }

    int last_id = sqlite3_last_insert_rowid(db);
    printf("The last Id of the inserted row is %d\n", last_id);
    return last_id;
}

s_user *users;

int check_login_callback(void *NotUsed, int argc, char **argv, char **azColName) {
    s_user *u = (s_user*)malloc(sizeof(s_user));
    u->next = NULL;
    if (!users)
        users = u;
    else {
        s_user *cur_u = users;
        while (cur_u->next)
            cur_u = cur_u->next;
        cur_u->next = u;
    }
    NotUsed = 0;
    for (int i = 0; i < argc; i++) {
        if (!mx_strcmp(azColName[i],"Id"))
            u->id = argv[i] ? mx_atoi(argv[i]) : 0;
        if (!mx_strcmp(azColName[i],"Login"))
            u->login = mx_strdup(argv[i]);
        if (!mx_strcmp(azColName[i],"Password"))
            u->password = mx_strdup(argv[i]);

        //printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    return 0;
}

int db_check_login(sqlite3 *db, char *login, char *password) {
    char *err_msg = 0;
    int rc;

    char sql[1024];
    snprintf(sql, sizeof(sql),
        "SELECT Id, Login, Password FROM Users WHERE Login = '%s';",login);
    rc = sqlite3_exec(db, sql, check_login_callback, 0, &err_msg);
    if (rc != SQLITE_OK ) {
        fprintf(stderr, "Failed to select data\n");
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
    }
    if (!users)
        return 0;
    int res_id = -1;
    if (!mx_strcmp(users->password, password))
        res_id = users->id;
    s_user *tmp;
    while (users != NULL) {
        tmp = users;
        users = users->next;
        //printf("!%d %s %s\n", tmp->id, tmp->login, tmp->password);
        free(tmp);
    }
    return res_id;
}
