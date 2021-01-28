//
// Created by Igor Khanenko on 1/26/21.
//

#include "server.h"

static char *get_file_path(char *filename) {
    char *file_path = NULL;

    file_path = mx_strjoin("server/media/voices/", filename);

    return file_path;
}

void mx_voice_file_receiver(t_server *serv, char *unique_name,
                            int user_index) {
    FILE *fp;
    char buffer[MAX_LEN];
    fp = fopen(get_file_path(unique_name), "wb");
    while (recv(serv->user_socket[user_index], buffer, MAX_LEN, 0)) {
        fwrite(buffer, 1, MAX_LEN, fp);
        memset(buffer, '\0', MAX_LEN);
    }
    fclose(fp);
    printf("Voice file receiving was successful!\n");
}
