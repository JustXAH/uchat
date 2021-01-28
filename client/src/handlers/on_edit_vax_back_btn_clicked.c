//
// Created by Maksym Tsyfir on 1/27/21.
//
#include "client.h"

extern t_chat_win chat_win;

void on_edit_vax_back_btn_clicked (GtkButton *btn) {
    gtk_stack_set_visible_child(chat_win.all_stack,
                                GTK_WIDGET(chat_win.my_profile_box));
    //printf("settings button clicked\n");
}
