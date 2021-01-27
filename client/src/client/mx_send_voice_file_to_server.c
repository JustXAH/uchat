//
// Created by Igor Khanenko on 1/26/21.
//

#include "client.h"

void mx_send_voice_file_to_server(t_system *sys, char *file_path) {
    FILE *fp = fopen(file_path, "rb");
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
        send(sys->sockfd, buffer, file_len_read, 0);
        memset(buffer, '\0', MAX_LEN);
    }
    fclose(fp);
}