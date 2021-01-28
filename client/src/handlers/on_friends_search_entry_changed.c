#include "client.h"

extern t_chat_win chat_win;
extern t_chat_list *contact_list;
extern t_client_st cl_listener;
extern t_chat *chat;

static void get_search_results();
void on_friends_search_entry_changed() {
    char *query = (char *)gtk_entry_get_text(GTK_ENTRY(chat_win.fsearch_entry));
    t_chat_list *con_buf = contact_list;

    if (cl_listener.fsearch == true) {
        GList *children, *iter;

        children = gtk_container_get_children(GTK_CONTAINER(chat_win.search_list));
        for (iter = children; iter != NULL; iter = g_list_next(iter))
            gtk_widget_destroy(GTK_WIDGET(iter->data));
        g_list_free(children);
    }
    if (strlen(query) > 0) { //User is searching
        //mx_printstr("entry search\n");
        gtk_stack_set_visible_child(chat_win.search_stack, 
                                    gtk_widget_get_parent(
                                        gtk_widget_get_parent(
                                            GTK_WIDGET(chat_win.search_list))));
        //mx_printstr("entry search 1\n");
        //sending search request
        chat->sys->login_substr = strdup(query);
        mx_user_search_by_substr_request(chat->sys, chat->json);
        free(chat->sys->login_substr);
        //mx_printstr("entry search 2\n");
        //Displaying search results
        get_search_results();
        cl_listener.fsearch = true;
        //mx_printstr("entry search 3\n");
    } else { //User stopped searching
        gtk_stack_set_visible_child(chat_win.search_stack, 
                                    gtk_widget_get_parent(
                                        gtk_widget_get_parent(
                                            GTK_WIDGET(chat_win.contacts_list))));

        cl_listener.fsearch = false;
    }
}
static void get_search_results() {
    while (cl_listener.pending_requests[USER_SEARCH_BY_SUBSTRING] == true);
    int count = chat->sys->found_usernames_count;
    
    if (count) {
        for (int i = 0; i < count; i++)
            gtk_container_add(GTK_CONTAINER(chat_win.search_list), 
                                gtk_label_new((const gchar *)
                                    chat->sys->found_usernames[i]));
        
        gtk_widget_show_all(GTK_WIDGET(chat_win.search_list));  
    }
}
