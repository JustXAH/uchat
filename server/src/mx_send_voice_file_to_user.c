//
// Created by Igor Khanenko on 1/27/21.
//

#include "server.h"

static char *get_file_path(char *filename) {
    char *file_path = NULL;
    char path_to_dir[21] = "server/media/voices/\0";

    file_path = mx_strjoin(path_to_dir, filename);

    memset(path_to_dir, '\0', 21);
    return file_path;
}

void mx_send_voice_file_to_user(char *filename, int user_socket) {
    FILE *fp = fopen(get_file_path(filename), "rb");
    char buffer[MAX_LEN];
    size_t file_len_read = 0;
    int parts = 1;

    if (fp == NULL) {
        perror("[-]Error in reading file.");
        exit(1);
    }

    while (!feof(fp)) {
        file_len_read = fread(buffer, 1, MAX_LEN, fp);
        printf("\nLEN_READ = %zu\n, PART %d:\n%s\n",file_len_read, parts, buffer);
        parts++;
//        fwrite(buffer, 1, MAX_LEN, dest);
        send(user_socket, buffer, file_len_read, 0);
        memset(buffer, '\0', MAX_LEN);
    }
    fclose(fp);
}