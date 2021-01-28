//
// Created by Igor Khanenko on 1/28/21.
//

#include "server.h"

char *mx_get_file_path(char *path_to_dir, char *filename) {
    char *file_path = NULL;
//    char path_to_dir[21] = "server/media/voices/\0";

    file_path = mx_strjoin(path_to_dir, filename);

//    memset(path_to_dir, '\0', 21);
    return file_path;
}
