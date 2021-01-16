#include "client.h"

extern t_chat *chat;
extern t_reg_win reg_win;
extern t_client_st cl_listener;
extern t_contact_list *contact_list;

void mb_auth_event_check() {
    //sleep(1);
    //printf("auth = %d logged_in = %d\n", cl_listener.authentication, cl_listener.logged_in);
    if (cl_listener.authentication == 1 && cl_listener.logged_in != 1) {
        gtk_show_chat_window(chat);
        cl_listener.logged_in = 1;
        //test lines below
        mb_contact_list_add(1, "Ckif");
        mb_contact_list_add(2, "Prick");

    } else if (cl_listener.authentication == 2) {
        mb_invalid_credentials_msg();
        cl_listener.authentication = 0;
        cl_listener.logged_in = 0;
        gtk_stack_set_visible_child_name(reg_win.stk, "log_window"); 
    }
}