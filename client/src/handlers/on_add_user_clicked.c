#include "client.h"

extern t_chat_list *contact_list;
extern t_client_st cl_listener;
extern t_chat_win chat_win;
extern t_chat *chat;

static void load_recieved_contact();
static void load_recieved_chat();
void on_add_user_clicked(GtkButton *btn) {

    mx_add_new_contact_request(chat->sys,  chat->user, 
                               chat->json, chat->sys->found_user_id);
    mx_add_new_chat_request(chat->sys,  chat->user, 
                               chat->json, chat->sys->found_user_id);

    load_recieved_contact();
    load_recieved_chat();
    mb_contact_list_add(chat->user->chats_id[chat->user->chats_count - 1],
                        chat->user->contacts_id[chat->user->contacts_count - 1],
                        chat->user->contacts_login[chat->user->contacts_count - 1]);
    //Show Chat window
    gtk_stack_set_visible_child(chat_win.all_stack, 
                                GTK_WIDGET(chat_win.msg_box));
    //Clear search_entry and display friends list
    cl_listener.fsearch = false;
    gtk_entry_set_text(GTK_ENTRY(chat_win.fsearch_entry), "");
    gtk_stack_set_visible_child(chat_win.search_stack, 
                                gtk_widget_get_parent(
                                    gtk_widget_get_parent(
                                        GTK_WIDGET(chat_win.contacts_list))));
    //Select newly added contact in the contact's list
    gtk_list_box_select_row(chat_win.contacts_list, 
                            gtk_widget_get_parent(
                                GTK_WIDGET(contact_list->contact_gui)));
    //Set the new chat in focus and display it;
    cl_listener.chat_in_focus = contact_list->chat_id;
    mb_display_chat_with_contact(contact_list->chat_id);
}
static void load_recieved_contact() {
    while (cl_listener.pending_requests[NEW_CONTACT]);

}
static void load_recieved_chat() {
    while (cl_listener.pending_requests[NEW_CHAT]);

    
}
