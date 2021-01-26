#include "client.h"

//extern t_chat_list *contact_list;
extern t_client_st cl_listener;
extern t_chat_win chat_win;
extern t_chat *chat;

static void load_recieved_profile();
void on_search_list_row_selected(GtkListBox *listbox, GtkListBoxRow *row) {
    gtk_stack_set_visible_child(chat_win.all_stack, 
                                GTK_WIDGET(chat_win.u_profile_box));
    mx_printstr("1\n");
    int index = gtk_list_box_row_get_index(row);
    char *user_name = strdup(chat->sys->found_usernames[index]);
    //gtk_label_set_text(chat_win.friend_login, user_name);
    //Request profile info
    chat->sys->searched_login = mx_strdup(chat->sys->found_usernames[index]);
    mx_user_search_by_login_request(chat->sys, chat->json);

    free(chat->sys->searched_login);

    load_recieved_profile();
    //mb_contact_list_add(int chat_id, int user_id, char *user_name)
    //printf("%s\n", user_name);
    free(user_name);
}
static void load_recieved_profile() {
    //while (cl_listener.pending_requests[USER_SEARCH_BY_LOGIN]);

    gtk_label_set_text(chat_win.friend_login, chat->sys->found_user_login);
}
