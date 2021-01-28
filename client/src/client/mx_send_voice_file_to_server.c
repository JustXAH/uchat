//
// Created by Igor Khanenko on 1/26/21.
//

#include "client.h"

void mx_send_file_to_server(t_system *sys, char *file_path) {
    FILE *fp = fopen(file_path, "rb");
    char buffer[MAX_LEN];
    size_t file_len_read = 0;

    if (fp == NULL) {
        printf("[-]Error in reading file!\n");
    }

    printf("\nOTPRAVKA START\n");
    while (!feof(fp)) {
        file_len_read = fread(buffer, 1, MAX_LEN, fp);
        send(sys->sockfd, buffer, file_len_read, 0);
        memset(buffer, '\0', MAX_LEN);
    }
    printf("\nOTPRAVKA END\n");
    fclose(fp);
}