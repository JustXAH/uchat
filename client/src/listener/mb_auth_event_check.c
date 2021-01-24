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
        gtk_show_chat_window(chat);
        cl_listener.logged_in = 1;
        //test lines below
        //cl_listener.my_id = 69;
        //cl_listener.my_name = mx_strdup("Horsecock");
        gtk_label_set_text(chat_win.welcome_user, cl_listener.my_name);
        mb_contact_list_add(1, 1, "Ckif");
        mb_contact_list_add(2, 2, "Prick");

    } else if (cl_listener.authentication == 2) {
    //Failed log in
        mb_invalid_credentials_msg();
        cl_listener.authentication = 0;
        cl_listener.logged_in = 0;
        //reg_win
        gtk_stack_set_visible_child_name(reg_win.stk, "log_window"); 
    }
}
