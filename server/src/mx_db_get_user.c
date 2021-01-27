#include "server.h"

t_user_info *gu_user_info;

static int get_user_callback(void *NotUsed, int argc, char **argv, char **azColName) {
    NotUsed = 0;
    for (int i = 0; i < argc; i++) {
        if (!mx_strcmp(azColName[i],"Login"))
            gu_user_info->login = mx_strdup(argv[i]);
        if (!mx_strcmp(azColName[i],"Picture"))
            gu_user_info->photo_file_id = mx_atoi(argv[i]);
    }
    return 0;
}

t_user_info* mx_db_get_user(sqlite3 *db, int user) {
    char *err_msg = 0;
    int rc;
    gu_user_info = (t_user_info*)malloc(sizeof(t_user_info));
    gu_user_info->id = user;
    char sql[1024];
    snprintf(sql, sizeof(sql),
             "SELECT Login,Picture FROM Users WHERE Id = '%d';",user);
    rc = sqlite3_exec(db, sql, get_user_callback, 0, &err_msg);
    if (rc != SQLITE_OK ) {
        fprintf(stderr, "Failed to select user data\n");
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
        gu_user_info->id = 0;
    }
    return gu_user_info;
}
