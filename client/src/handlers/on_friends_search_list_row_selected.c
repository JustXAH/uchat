#include "client.h"

//extern t_chat_list *contact_list;
extern t_client_st cl_listener;
extern t_chat_win chat_win;
extern t_chat *chat;

void on_search_list_row_selected(GtkListBox *listbox, GtkListBoxRow *row) {
    gtk_stack_set_visible_child(chat_win.all_stack, 
                                GTK_WIDGET(chat_win.u_profile_box));

    int index = gtk_list_box_row_get_index(row);
    char *user_name = strdup(chat->sys->found_usernames[index]);
    gtk_label_set_text(chat_win.friend_login, user_name);
    printf("%s\n", user_name);
    free(user_name);
}
