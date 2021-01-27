//
// Created by Igor Khanenko on 1/27/21.
//

#include "server.h"

void mx_media_dirs_creator() {
    if (mkdir("server/media", 0777) == 0) {
        printf("Successfully created media folder!\n");
    } else {
        printf("ERROR while creating folder media!\n");
    }
    if (mkdir("server/media/voices", 0777) == 0) {
        printf("Successfully created voices folder!\n");
    } else {
        printf("ERROR while creating folder voices!\n");
    }
    if (mkdir("server/media/users_pic", 0777) == 0) {
        printf("Successfully created users_pic folder!\n");
    } else {
        printf("ERROR while creating folder users_pic!\n");
    }
}
