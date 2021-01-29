#include "client.h"

extern t_chat *chat;
extern t_chat_win chat_win;
extern t_message *msg;
extern t_client_st cl_listener;
extern t_chat_list *contact_list;

void on_vox_swap_btn_clicked(GtkButton *btn) {
    if (cl_listener.vox_not_msg) {
        gtk_stack_set_visible_child(chat_win.msg_entry_stk, 
                                    GTK_WIDGET(chat_win.msg_entry_box));
        cl_listener.vox_not_msg = false;
    }
    else {
        gtk_stack_set_visible_child(chat_win.msg_entry_stk, 
                                    GTK_WIDGET(chat_win.vox_entry_box));
        cl_listener.vox_not_msg = true;
    }
}



