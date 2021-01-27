#include "server.h"

int *guv_id;
char **guv_filename;
char **guv_voice_name;

static int mx_get_user_voices_callback(void *NotUsed, int argc, char **argv, char **azColName) {
    int index=0, value_id=0;
    char *value_filename;
    char *value_voice_name;
    NotUsed = 0;
    for (int i = 0; i < argc; i++) {
        if (!mx_strcmp(azColName[i],"Number"))
            index = mx_atoi(argv[i]);
        if (!mx_strcmp(azColName[i],"FileId"))
            value_id = mx_atoi(argv[i]);
        if (!mx_strcmp(azColName[i],"FileName"))
            value_filename = mx_strdup(argv[i]);
        if (!mx_strcmp(azColName[i],"VoiceName"))
            value_voice_name = mx_strdup(argv[i]);
    }
    guv_id[index] = value_id;
    guv_filename[index] = value_filename;
    guv_voice_name[index] = value_voice_name;
    return 0;
}

t_voice *mx_db_get_users_voices(sqlite3 *db, int user) {
    char *err_msg = 0;
    int rc;
    guv_id = (int *)malloc(NUMBER_VOICES*sizeof(int));
    guv_filename = (char **)malloc(NUMBER_VOICES*sizeof(char*));
    guv_voice_name = (char **)malloc(NUMBER_VOICES*sizeof(char*));
    for (int i = 0; i < NUMBER_VOICES; i++) {
        guv_id[i] = 0;
        guv_filename[i] = NULL;
        guv_voice_name[i] = NULL;
    }
    char sql[1024];
    snprintf(sql, sizeof(sql),
             "SELECT Number,FileId,FileName,VoiceName FROM Voices INNER JOIN Files ON Voices.FileId=Files.Id WHERE (User = '%d');",user);


    rc = sqlite3_exec(db, sql, mx_get_user_voices_callback, 0, &err_msg);

    if (rc != SQLITE_OK ) {
        fprintf(stderr, "Failed to select data\n");
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
        return NULL;
    }
    t_voice * guv = (t_voice *)malloc(sizeof(t_voice));
    guv->id = guv_id;
    guv->filename = guv_filename;
    guv->voice_name = guv_voice_name;
    return guv;
}
