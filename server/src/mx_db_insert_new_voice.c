#include "server.h"

char* mx_db_insert_new_voice(sqlite3 *db, int user, int number, char *filename, char *voice_name){
    char *err_msg = 0;
    int rc;

    //ckeck voice EXISTS

    //

    int file_id = mx_db_insert_new_file(db, filename);

    char sql[1024];
    snprintf(sql, sizeof(sql),
             "INSERT INTO Voices(User,Number,FileId,VoiceName) VALUES ('%d','%d','%d','%s');",user,number,file_id,voice_name);

    rc = sqlite3_exec(db, sql, 0, 0, &err_msg);

    if (rc != SQLITE_OK ) {
        fprintf(stderr, "Failed to insert voice\n");
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
    } else {
        fprintf(stdout, "New voice created successfully\n");
    }

    //int last_id = sqlite3_last_insert_rowid(db);
    return mx_db_get_filename(db, file_id);;
}
