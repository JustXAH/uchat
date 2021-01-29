#include "client.h"

extern t_chat_win chat_win;
extern t_chat_list *contact_list;
extern t_client_st cl_listener;
extern t_chat *chat;
extern t_message *chat_history;

static int get_chat_id(char *user_name, int user_id) {
    for (int i = 0; i < chat->user->chats_count; i++)
        if (!strcmp(chat->user->chats_name[i], user_name)) 
            return chat->user->chats_id[i];

    cl_listener.pending_requests[NEW_CHAT] = true;
    mx_add_new_chat_request(chat->sys, chat->user, chat->json, user_id);
    while (cl_listener.pending_requests[NEW_CHAT]);

    for (int i = 0; i < chat->user->chats_count; i++)
        if (!strcmp(chat->user->chats_name[i], user_name)) 
            return chat->user->chats_id[i];
    return -1;
}

void on_contact_list_row_selected(GtkListBox *listbox, GtkListBoxRow *row) {
    if (cl_listener.dont_bother_search)
        return;
    t_chat_list *con_buf = contact_list;
    //int index = gtk_list_box_row_get_index(row);


    gtk_stack_set_visible_child(chat_win.all_stack, GTK_WIDGET(chat_win.msg_box));

    while (con_buf->next_chat) {
        if (gtk_list_box_row_is_selected(GTK_LIST_BOX_ROW(gtk_widget_get_parent(con_buf->contact_gui))))
            break;
        else
            con_buf = con_buf->next_chat;
    }
    int id = get_chat_id(con_buf->user_name, con_buf->user_id);
    cl_listener.chat_in_focus = id;
    cl_listener.user_in_focus = con_buf->user_id;

    //mx_get_history_chat_request(chat->sys, chat->user, chat->json, cl_listener.chat_in_focus);
    mb_display_chat_with_contact(id);
}
