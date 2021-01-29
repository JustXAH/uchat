#include "client.h"

extern t_chat_list *contact_list;
extern t_client_st cl_listener;
extern t_chat_win chat_win;
extern t_chat *chat;

static void load_recieved_contact() {
    while (cl_listener.pending_requests[NEW_CONTACT]);
}
static void load_recieved_chat() {
    while (cl_listener.pending_requests[NEW_CHAT]);
}
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
////////////////////////////////////////////////////////////////////
void on_add_user_clicked(GtkButton *btn) {
    cl_listener.just_added_new_friend = true;
    cl_listener.dont_bother_search = true;
    mx_add_new_contact_request(chat->sys,  chat->user, 
                               chat->json, chat->sys->found_user_id);
    load_recieved_contact();
    mx_add_new_chat_request(chat->sys,  chat->user, 
                               chat->json, chat->sys->found_user_id);
    load_recieved_chat();

    //Show Chat window
    gtk_stack_set_visible_child(chat_win.all_stack, 
                                GTK_WIDGET(chat_win.msg_box));



    //Select newly added contact in the contact's list
    gtk_list_box_select_row(chat_win.contacts_list, 
                            GTK_LIST_BOX_ROW(
                                gtk_widget_get_parent(
                                    GTK_WIDGET(contact_list->contact_gui))));

    //Set the new chat in focus and display it;
    cl_listener.chat_in_focus = get_chat_id(cl_listener.requested_user_name, cl_listener.requested_user_id);
   
    mx_printint(cl_listener.chat_in_focus);
    mx_printstr(" <- chat in focus\n");



    mb_display_chat_with_contact(cl_listener.chat_in_focus);
    cl_listener.just_added_new_friend = false;

    //Clear search_entry and display friends list
    cl_listener.fsearch = false;
    /*gtk_list_box_set_selection_mode(chat_win.search_list, GTK_SELECTION_NONE);
    gtk_entry_set_text(GTK_ENTRY(chat_win.fsearch_entry), "");
    gtk_stack_set_visible_child(chat_win.search_stack, 
                                gtk_widget_get_parent(
                                    gtk_widget_get_parent(
                                        GTK_WIDGET(chat_win.contacts_list))));*/

    mx_printstr("on_add_user_clicked finished\n");
    cl_listener.dont_bother_search = false;
}
