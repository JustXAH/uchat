//
// Created by Igor Khanenko on 1/27/21.
//

#include "client.h"

void mx_cache_dir_creator() {
    struct stat st = {0};

    if (stat("client/cache", &st) == -1) {
        if (mkdir("client/cache", 0777) == 0) {
            printf("Successfully created cache folder!\n");
        } else {
            printf("ERROR while creating cache folder!\n");
        }
    }
}
