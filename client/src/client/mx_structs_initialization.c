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
    sys->exit = false;

    user->login = NULL;
    user->password = NULL;
    user->my_id = 0;
    user->who_online_count = 0;
}
