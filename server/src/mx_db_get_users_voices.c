#include "server.h"

int *guv;

static int mx_get_user_voices_callback(void *NotUsed, int argc, char **argv, char **azColName) {
    int index=0, value=0;
    NotUsed = 0;
    for (int i = 0; i < argc; i++) {
        if (!mx_strcmp(azColName[i],"Number"))
            index = mx_atoi(argv[i]);
        if (!mx_strcmp(azColName[i],"FileId"))
            value = mx_atoi(argv[i]);
    }
    guv[index] = value;
    return 0;
}

int *mx_db_get_users_voices(sqlite3 *db, int user) {
    char *err_msg = 0;
    int rc;
    guv = (int *)malloc(NUMBER_VOICES*sizeof(int));
    for (int i = 0; i < NUMBER_VOICES; i++)
        guv[i] = 0;
    char sql[1024];
    snprintf(sql, sizeof(sql),
             "SELECT Number,FileId FROM Voices WHERE (User = '%d');",user);

    rc = sqlite3_exec(db, sql, mx_get_user_voices_callback, 0, &err_msg);

    if (rc != SQLITE_OK ) {
        fprintf(stderr, "Failed to select data\n");
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
    }

    return guv;
}
