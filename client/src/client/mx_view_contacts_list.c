//
// Created by Igor Khanenko on 10.01.2021.
//

#include "client.h"

void mx_view_contacts_list(t_system *sys, t_user *user) {
    if (user->contacts) {
        for (int i = 0; user->contacts[i] != 0; i++) {
            printf("Contact #%d ID: %d\n", i, user->contacts[i]);
//            write(1, "\n", 1);
        }
    }
}
