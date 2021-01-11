//
// Created by mac on 10.01.2021.
//

#include "client.h"

void mx_client_menu(t_system *sys, t_user *user) {
    char choice[1];

    write(1, "\n\nWelcome to the G-Chat menu! Select the option you need:\n", 58);
    write(1, "'1' - view the list of contacts\n", 32);
    write(1, "'2' - view the list of chats\n", 29);
    write(1, "'3' - search people\n", 20);
    write(1, "'4' - leave the chat\n", 21);

    scanf("%s", choice);
    write(1, "\n", 1);

    if (strcmp(choice, "1") == 0) {
        mx_view_contacts_list(sys, user);
    }
    else if (strcmp(choice, "2") == 0) {
        mx_view_chats_list(sys, user);
    }
    else if (strcmp(choice, "3") == 0) {
        mx_user_search(sys, user);
    }
    else if (strcmp(choice, "4") == 0) { // leave the chat
        sys->exit = true;
    }
    else {
        write(1, "Incorrect answer\n", 17);
    }
}
