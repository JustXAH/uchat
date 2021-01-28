//
// Created by Igor Khanenko on 1/28/21.
//

#include "server.h"

//static char *get_file_path(char *filename) {
//    char *file_path = NULL;
//
//    file_path = mx_strjoin("server/media/users_pic/", filename);
//
//    return file_path;
//}

void mx_user_pic_receiver(t_server *serv, char *unique_name, int file_size,
                            int user_index) {
    FILE *fp = fopen(mx_get_file_path("server/media/users_pic/", unique_name),
                     "wb");
    char buffer[MAX_LEN];
    int len_recv = 0;
    int total = 0;

    printf("\nPRIEM START\n");
    while (total != file_size) {
        len_recv = recv(serv->user_socket[user_index], buffer, MAX_LEN, 0);
        total += len_recv;
        printf("FILE_SIZe: |%d|\nTOTAL RECV: |%d|\n", file_size, total);
        fwrite(buffer, 1, MAX_LEN, fp);
        memset(buffer, '\0', MAX_LEN);
    }
    printf("\nPRIEM END\n");
    fclose(fp);
    printf("User pic receiving was successful!\n");
}
