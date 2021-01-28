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

char *mx_file_receiving(t_system *sys, t_json *json) {
    char *file_path = get_file_path(json->FILENAME->valuestring);
    FILE *fp = fopen(file_path, "wb");
    char buffer[MAX_LEN];

    while (recv(sys->sockfd, buffer, MAX_LEN, 0)) {
        fwrite(buffer, 1, MAX_LEN, fp);
        memset(buffer, '\0', MAX_LEN);
    }
    fclose(fp);
    return file_path;
}
