#include "client.h"

extern t_chat_list *contact_list;
extern t_client_st cl_listener;
extern t_chat_win chat_win;
extern t_chat *chat;

static void load_recieved_contact();
static void load_recieved_chat();
void on_add_user_clicked(GtkButton *btn) {
    cl_listener.just_added_new_friend = true;
    mx_add_new_contact_request(chat->sys,  chat->user, 
                               chat->json, chat->sys->found_user_id);
    load_recieved_contact();
    mx_add_new_chat_request(chat->sys,  chat->user, 
                               chat->json, chat->sys->found_user_id);
    load_recieved_chat();


    //printf("chats count : %d ", chat->user->chats_count)
    mb_contact_list_add(chat->user->chats_id[chat->user->chats_count - 1],
                        chat->user->contacts_id[chat->user->contacts_count - 1],
                        chat->user->contacts_login[chat->user->contacts_count - 1], false);

    mx_printstr("on_add_user_clicked 2\n");
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
                            GTK_LIST_BOX_ROW(
                                gtk_widget_get_parent(
                                    GTK_WIDGET(contact_list->contact_gui))));

    mx_printstr("on_add_user_clicked 5\n");

    //Set the new chat in focus and display it;
    cl_listener.chat_in_focus = contact_list->chat_id;
    mx_printint(cl_listener.chat_in_focus);
    mx_printstr(" <- chat in focus\n");
    mx_get_history_chat_request(chat->sys, chat->user, chat->json, cl_listener.chat_in_focus);

    mb_display_chat_with_contact(contact_list->chat_id);
    cl_listener.just_added_new_friend = false;
    mx_printstr("on_add_user_clicked finished\n");
}
static void load_recieved_contact() {
    while (cl_listener.pending_requests[NEW_CONTACT]);
}
static void load_recieved_chat() {
    while (cl_listener.pending_requests[NEW_CHAT]);
}
