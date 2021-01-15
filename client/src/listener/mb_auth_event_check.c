#include "client.h"

extern t_chat *chat;
extern t_client_st cl_listener;

void mb_auth_event_check() {
    //sleep(1);
    //printf("auth = %d logged_in = %d\n", cl_listener.authentication, cl_listener.logged_in);
    if (cl_listener.authentication == 1 && !cl_listener.logged_in) {
        gtk_show_chat_window(chat);
        cl_listener.logged_in = true;
    }
    else if (cl_listener.authentication == 2) {
        mb_invalid_credentials_msg();
        cl_listener.authentication = 0;
    }
}