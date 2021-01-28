//
// Created by Igor Khanenko on 1/5/21.
//

#include "client.h"

void mx_structs_initialization(t_system *sys, t_user *user) {
    sys->sockfd = 0;
    sys->first_reg = true;
    sys->reg_request = false;
    sys->reg_confirmation = false;
    sys->authentication = false;
    sys->menu = false;
    sys->chat = false;
    sys->voice_play = true;
    sys->exit = false;
    sys->filename = NULL;
    sys->file_path = NULL;
    sys->voice_name = NULL;
    sys->position = -1;
    sys->exit = 0;
    sys->found_usernames = NULL;

    user->login = NULL;
    user->password = NULL;
    user->hash_password = NULL;
    user->my_id = 0;
    user->who_online_count = 0;
    user->who_online = NULL;
    user->voices_name = NULL;
    user->user_pic_id = 0;
    user->voices_id = (int *)malloc(sizeof(int) * NUMBER_VOICES);
    for (int i = 0; i != NUMBER_VOICES; i++) {
        user->voices_id[i] = 0;
    }
}
