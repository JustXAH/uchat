#include "client.h"

extern t_chat_win chat_win;
extern t_chat *chat;
extern t_client_st cl_listener;
//----------------------------------------------------------------------------//
void mb_display_chat_with_contact(int chat_id) {
    GtkListBoxRow *temp = gtk_list_box_get_row_at_index(chat_win.msg_viewer,0);
    while (temp) {
        gtk_widget_destroy(GTK_WIDGET(temp));
        temp = gtk_list_box_get_row_at_index(chat_win.msg_viewer,0);
    }
    mx_get_history_chat_request(chat->sys, chat->user, chat->json, cl_listener.chat_in_focus);
}///////////////////////////////////////////////////////////////////////////////
/*
static void mb_load_chat_history(t_message *history) {
    mb_clear_chat_viewer();
    while (history) {
        //printf("%s\n",history->text);
        mb_display_msg(history);
        history = history->next;
    }
}*/

