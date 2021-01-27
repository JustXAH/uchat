#include "client.h"

extern t_chat_win chat_win;
extern t_chat_list *contact_list;
extern t_client_st cl_listener;

void on_contact_list_row_selected(GtkListBox *listbox, GtkListBoxRow *row) {
    gtk_stack_set_visible_child(chat_win.all_stack, GTK_WIDGET(chat_win.msg_box));
    t_chat_list *con_buff = contact_list;
    int index = gtk_list_box_row_get_index(row);

    for (;index--;con_buff = con_buff->next_chat);
    cl_listener.chat_in_focus = con_buff->chat_id;

    mb_display_chat_with_contact(con_buff->chat_id);
}
