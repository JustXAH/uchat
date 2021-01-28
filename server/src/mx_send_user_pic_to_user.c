//
// Created by Igor Khanenko on 1/28/21.
//

#include "server.h"

//static char *get_user_pic_path(char *filename) {
//    char *file_path = NULL;
//    char path_to_dir[24] = "server/media/users_pic/\0";
//
//    file_path = mx_strjoin(path_to_dir, filename);
//
//    memset(path_to_dir, '\0', 24);
//    return file_path;
//}

void mx_send_user_pic_to_user(char *file_path, int user_socket) {
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
