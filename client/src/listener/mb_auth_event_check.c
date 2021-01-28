#include "client.h"

extern t_chat *chat;
extern t_reg_win reg_win;
extern t_client_st cl_listener;
extern t_chat_list *contact_list;
extern t_chat_win chat_win;

void mb_auth_event_check() {
    //sleep(1);

    if (cl_listener.authentication == 1 && cl_listener.logged_in != 1) {
    //Successful log in
        mx_printstr("logging in\n");
        gtk_show_chat_window(chat);
        cl_listener.logged_in = 1;

        gtk_label_set_text(chat_win.welcome_user, cl_listener.my_name);
    } 
    else if (cl_listener.authentication == 2) {
    //Failed log in
        mb_invalid_credentials_msg();
        cl_listener.authentication = 0;
        cl_listener.logged_in = 0;
        //reg_win
        gtk_stack_set_visible_child_name(reg_win.stk, "log_window"); 
    }
}
