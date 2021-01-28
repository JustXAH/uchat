//
// Created by Igor Khanenko on 1/28/21.
//

#include "server.h"

int mx_file_size_measurement(char *file_path) {
    struct stat lt;
    off_t file_size = 0;

    stat(file_path, &lt);
    file_size = lt.st_size;
    return (int)file_size;
}
