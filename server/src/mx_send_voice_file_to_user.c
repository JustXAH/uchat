//
// Created by Igor Khanenko on 1/28/21.
//

#include "server.h"

//static char *get_voice_file_path(char *filename) {
//    char *file_path = NULL;
//    char path_to_dir[21] = "server/media/voices/\0";
//
//    file_path = mx_strjoin(path_to_dir, filename);
//
//    memset(path_to_dir, '\0', 21);
//    return file_path;
//}

void mx_send_voice_file_to_user(t_server *serv, char *file_path,
                                int user_socket) {
    FILE *fp = fopen(file_path, "rb");
    char buffer[MAX_LEN];
    size_t file_len_read = 0;

    if (fp == NULL) {
        printf("[-]Error in reading file!\n");
    }

    while (!feof(fp)) {
        file_len_read = fread(buffer, 1, MAX_LEN, fp);
        send(user_socket, buffer, file_len_read, 0);
        memset(buffer, '\0', MAX_LEN);
    }
    fclose(fp);
}
