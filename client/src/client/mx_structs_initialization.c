//
// Created by Igor Khanenko on 1/5/21.
//

#include "client.h"

void mx_structs_initialization(t_system *sys, t_user *user) {
    sys->sockfd = 0;
    sys->first_reg = true;
    sys->registration = false;
    sys->authentication = false;
    sys->menu = false;
    sys->chat = false;
    sys->exit = false;

    user->login = NULL;
    user->password = NULL;
    user->contacts = NULL;
    user->chats = NULL;
    user->my_id = 0;
}
