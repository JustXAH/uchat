//
// Created by mac on 10.01.2021.
//

#include "client.h"

void mx_chat_event(t_system *sys, t_user *user, pthread_t thread) {
    char buff[MAX_LEN];

//    bool first_entry = true;
//    if (sys->authentication == true) {
    for (;;) {

        if (sys->authentication == true && sys->menu == true) {
            mx_client_menu(sys, user);
        }
        else if (sys->chat == true) {
            usleep(750);
            //остановка потока read_server, на момент ввода сообщения юзером
//                pthread_mutex_lock(&sys->mutex);
            write(1, "\n\nEnter your message: ", 22);

            scanf("%s", buff);

            if (strncmp(buff, "exit", 4) == 0) {
                sys->exit = true;
            }

            mx_sending_messages(sys, user, buff);
            memset(buff, '\0', sizeof(buff));
            //восстановление потока read_server, после ввода сообщения юзером
//                pthread_mutex_unlock(&sys->mutex);

        }
        if (sys->exit == true) {
            write(1, "\n\nGoodbye, ", 11);
            write(1, user->login, strlen(user->login));
            write(1, "! See you in G-chat again!\n", 27);
            pthread_cancel(thread);
            break;
        }
    }
}
