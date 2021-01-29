#include "client.h"

extern t_chat_win chat_win;
extern t_client_st cl_listener;

void on_settings_btn_clicked(GtkButton *btn) {
    gtk_label_set_text(chat_win.profile_login, cl_listener.my_name);
    gtk_stack_set_visible_child(chat_win.all_stack, 
                            GTK_WIDGET(chat_win.my_profile_box));
    //printf("settings button clicked\n");                        
}
