//
// Created by Igor Khanenko on 1/5/21.
//

#include "client.h"

void mx_login_or_register(t_system *sys, t_user *user) {
    char *login_json = NULL;
    char choice[1];

//    sys->registration = false;
    write(1, "Welcome to G-Chat!\n", 19);
    write(1, "Please choose the option you need:\n", 35);
    write(1, "'1' - log into the G-chat account\n", 34);
    write(1, "'2' - register a new account\n", 29);

    scanf("%s", choice);
    write(1, "\n", 1);

    if (strcmp(choice, "1") == 0) {  //Log in!;
        sys->registration = true;
        login_json = mx_create_user_profile(sys, user);
        write(sys->sockfd, login_json, mx_strlen(login_json));
    }
    else if (strcmp(choice, "2") == 0) {
        sys->registration = false;
        login_json = mx_create_user_profile(sys, user);
        write(sys->sockfd, login_json, mx_strlen(login_json));
    }
    else {
        write(1, "Incorrect answer!\n", 18);
    }

    if (login_json != NULL)
        free(login_json);
}
