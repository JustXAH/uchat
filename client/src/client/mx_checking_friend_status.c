//
// Created by Igor Khanenko on 1/29/21.
//

#include "client.h"

bool mx_checking_friend_status(t_user *user, int contact_id) {
    bool status = false;

    for (int i = 0; i < user->contacts_count; i++) {
        if (user->contacts_id[i] == contact_id) {
            status = true;
            break;
        }
    }
    return status;
}
