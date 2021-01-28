//
// Created by Igor Khanenko on 1/27/21.
//

#include "client.h"

static char *get_file_path(char *filename) {
    char *file_path = NULL;
    char path_to_dir[14] = "client/cache/\0";

    file_path = mx_strjoin(path_to_dir, filename);

    memset(path_to_dir, '\0', 14);
    return file_path;
}

char *mx_file_receiving(t_system *sys, char *filename, int file_size) {
    char *file_path = get_file_path(filename);
    char buffer[MAX_LEN];
    FILE *fp = fopen(file_path, "wb");
    int len_recv = 0;
    int total = 0;

    printf("\nPRIEM START\n");
    while (total != file_size) {
//        if (total > file_size ) {
//            sys->voice_play = false;
//            break;
//        }
        len_recv = recv(sys->sockfd, buffer, MAX_LEN, 0);
        total += len_recv;
        printf("FILE_SIZe: |%d|\nTOTAL RECV: |%d|\n", file_size, total);
        fwrite(buffer, 1, MAX_LEN, fp);
        memset(buffer, '\0', MAX_LEN);
    }
    memset(buffer, '\0', MAX_LEN);
    printf("\nPRIEM END\n");
    fclose(fp);
    return file_path;
}
