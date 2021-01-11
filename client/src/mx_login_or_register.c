//
// Created by Igor Khanenko on 1/5/21.
//

#include "client.h"

void mx_login_or_register(t_client *cli) {
    char *login_json;
    char choice[1];
    bool registration = false;

    write(1, "Welcome to G-Chat!\n", 19);
    write(1, "Please enter:\n", 14);
    write(1, "'1' - if you already have an account and want to log in\n", 56);
    write(1, "'2' - if you want to register a new account\n", 44);

    scanf("%s", choice);
    write(1, "\n", 1);

    if (strcmp(choice, "1") == 0) {  //Log in!;
        login_json = mx_create_user_profile(cli, registration);
        write(cli->sockfd, login_json, mx_strlen(login_json));
    }
    else if (strcmp(choice, "2") == 0) {
        registration = true;
        login_json = mx_create_user_profile(cli, registration);
        write(cli->sockfd, login_json, mx_strlen(login_json));
    }
    else {
        write(1, "Incorrect answer!\n", 18);
    }

    if (malloc_size(login_json))
        free(login_json);
}
