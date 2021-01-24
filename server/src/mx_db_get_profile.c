#include "server.h"

t_user_info *gp_user_profile;

static int get_profile_callback(void *NotUsed, int argc, char **argv, char **azColName) {
    NotUsed = 0;
    for (int i = 0; i < argc; i++) {
        if (!mx_strcmp(azColName[i],"Login"))
            gp_user_profile->login = mx_strdup(argv[i]);
    }
    return 0;
}

t_user_info* mx_db_get_profile(sqlite3 *db, int user) {
    char *err_msg = 0;
    int rc;
    gp_user_profile = (t_user_info*)malloc(sizeof(t_user_info));
    gp_user_profile->id = user;
    char sql[1024];
    snprintf(sql, sizeof(sql),
             "SELECT Login FROM Users WHERE Id = '%d';",user);
    rc = sqlite3_exec(db, sql, get_profile_callback, 0, &err_msg);
    if (rc != SQLITE_OK ) {
        fprintf(stderr, "Failed to select data\n");
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
        gp_user_profile->id = 0;
    }
    return gp_user_profile;
}
