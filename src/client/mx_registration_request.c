//
// Created by mac on 11.01.2021.
//

#include "client.h"

void mx_registration_request(t_system *sys, t_user *user) {
    char *str_user_json;

    sys->registration = false;

    if (malloc_usable_size(user->login)) {
        free(user->login);
    }
    if (malloc_usable_size(user->password)) {
        free(user->password);
    }
    str_user_json = mx_create_user_profile(sys, user);
    write(sys->sockfd, str_user_json, strlen(str_user_json));
    free(str_user_json);
}
