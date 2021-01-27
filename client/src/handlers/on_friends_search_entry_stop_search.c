#include "client.h"

extern t_chat_win chat_win;
//extern t_chat_list *contact_list;
extern t_client_st cl_listener;
//extern t_chat *chat;

void on_friends_search_entry_stop_search() {
    printf("search stop\n");
    gtk_entry_set_text(GTK_ENTRY(chat_win.fsearch_entry), "");
    gtk_stack_set_visible_child(chat_win.search_stack, 
                                gtk_widget_get_parent(
                                    gtk_widget_get_parent(
                                        GTK_WIDGET(chat_win.contacts_list))));

    cl_listener.fsearch = false;
}