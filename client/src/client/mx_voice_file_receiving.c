//
// Created by Igor Khanenko on 1/27/21.
//

#include "client.h"

//static char *get_file_path(char *filename) {
//    char *file_path = NULL;
//    char path_to_dir[21] = "server/media/voices/\0";
//
//    file_path = mx_strjoin(path_to_dir, filename);
//
//    memset(path_to_dir, '\0', 21);
//    return file_path;
//}

void mx_voice_file_receiving(t_system *sys) {
    FILE *fp;
    char buffer[MAX_LEN];

    if (mkdir("client/cache", 0777) == 0) {
        printf("Successfully created cache folder!\n");
        fp = fopen("client/cache/voice_message", "wb");
        while (recv(sys->sockfd, buffer, MAX_LEN, 0)) {
            fwrite(buffer, 1, MAX_LEN, fp);
            memset(buffer, '\0', MAX_LEN);
        }
        fclose(fp);
        printf("Voice file receiving was successful!");
    }
    else {
        printf("ERROR while creating folder cache!\n");
    }
}