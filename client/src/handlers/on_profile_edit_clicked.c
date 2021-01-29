//
// Created by Maksym Tsyfir on 1/26/21.
//

#include "client.h"

extern t_chat_win chat_win;
extern t_client_st cl_listener;

void on_profile_edit_clicked(GtkButton *btn) {
    //printf("TEXT %s\n\n",cl_listener.my_name);
    //gtk_label_set_text(chat_win.profile_login, cl_listener.my_name);
    gtk_stack_set_visible_child(chat_win.all_stack,
                                GTK_WIDGET(chat_win.edit_profile));
    //printf("settings button clicked\n");
}

