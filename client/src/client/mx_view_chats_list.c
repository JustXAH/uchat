//
// Created by Igor Khanenko on 10.01.2021.
//

#include "client.h"

void mx_view_chats_list(t_system *sys, t_user *user) {
    if (user->chats_id) {
        for (int i = 0; user->chats_id[i] != 0; i++) {
            printf("Chats #%d ID: %d\n", i, user->chats_id[i]);
//            write(1, "\n", 1);
        }
    }
    sys->menu = false;
    sys->chat = true;
}
