#include "client.h"

extern t_chat_win chat_win;
extern t_chat_list *contact_list;
extern t_client_st cl_listener;
extern t_chat *chat;
extern t_message *chat_history;

void on_contact_list_row_selected(GtkListBox *listbox, GtkListBoxRow *row) {
    if (cl_listener.just_added_new_friend)
        return;
    t_chat_list *con_buff = contact_list;
    int index = gtk_list_box_row_get_index(row);

    mx_get_history_chat_request(chat->sys, chat->user, chat->json, cl_listener.chat_in_focus);

    gtk_stack_set_visible_child(chat_win.all_stack, GTK_WIDGET(chat_win.msg_box));

    for (;index--;con_buff = con_buff->next_chat);
    cl_listener.chat_in_focus = con_buff->chat_id;

    mb_display_chat_with_contact(con_buff->chat_id);
}
