#include "client.h"

//extern t_chat_list *contact_list;
extern t_client_st cl_listener;
extern t_chat_win chat_win;
extern t_chat *chat;

static void load_recieved_profile();
void on_search_list_row_selected(GtkListBox *listbox, GtkListBoxRow *row) {
    //int index = gtk_list_box_row_get_index(gtk_list_box_get_selected_row(chat_win.search_list));
    int index = 0;

    for (int i = 0; i < chat->sys->found_usernames_count; i++) {
         if (gtk_list_box_row_is_selected(GTK_LIST_BOX_ROW(gtk_widget_get_parent(chat_win.fresults[i])))) {
            index = i;
            break;
         }
    }
    char *user_name = strdup(chat->sys->found_usernames[index]);

    //Request profile info
    chat->sys->searched_login = mx_strdup(chat->sys->found_usernames[index]);

    mx_user_search_by_login_request(chat->sys, chat->json);
    load_recieved_profile();

    gtk_stack_set_visible_child(chat_win.all_stack, 
                                GTK_WIDGET(chat_win.u_profile_box));

    free(chat->sys->searched_login);
    free(user_name);

}
static void load_recieved_profile() {
    while (cl_listener.pending_requests[USER_SEARCH_BY_LOGIN]);

    if (cl_listener.requested_user_name)
        free(cl_listener.requested_user_name);

    cl_listener.requested_user_name = mx_strdup(chat->sys->found_user_login);
    cl_listener.requested_user_id = chat->sys->found_user_id;
    if (mx_checking_friend_status(chat->user, cl_listener.requested_user_id)) {
     gtk_stack_set_visible_child(chat_win.add_remove_stk, 
                                GTK_WIDGET(chat_win.remove_user));       
    }
    else {
     gtk_stack_set_visible_child(chat_win.add_remove_stk, 
                                GTK_WIDGET(chat_win.add_user));    
    }
    gtk_label_set_text(chat_win.friend_login, chat->sys->found_user_login);
}

