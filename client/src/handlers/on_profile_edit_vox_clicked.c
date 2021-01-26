//
// Created by Maksym Tsyfir on 1/26/21.
//

#include "client.h"

extern t_chat_win chat_win;

void on_profile_edit_vox_clicked(GtkButton *btn) {
    gtk_stack_set_visible_child(chat_win.all_stack,
                                GTK_WIDGET(chat_win.edit_vax_box));
    //printf("settings button clicked\n");
}
