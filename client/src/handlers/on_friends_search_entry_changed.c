#include "client.h"

extern t_chat_win chat_win;
extern t_chat_list *contact_list;
extern t_client_st cl_listener;
extern t_chat *chat;

static void get_search_results();
void on_friends_search_entry_changed() {
    if (cl_listener.dont_bother_search)
        return;
    printf("entry search started\n");
    char *query = query = (char *)gtk_entry_get_text(GTK_ENTRY(chat_win.fsearch_entry));
    t_chat_list *con_buf = contact_list;

    if (strlen(query) > 0) {
        //Clearing old results
        gtk_list_box_set_selection_mode(chat_win.search_list, GTK_SELECTION_NONE);
        GList *children, *iter;
        children = gtk_container_get_children(GTK_CONTAINER(chat_win.search_list));
        for (iter = children; iter != NULL; iter = g_list_next(iter))
            gtk_widget_destroy(GTK_WIDGET(iter->data));
        g_list_free(children);

        chat_win.search_list = GTK_LIST_BOX(gtk_builder_get_object(chat->sys->builder,
                                                        "search_list"));   
         //User is searching
        //printf("entry search\n");
        gtk_list_box_set_selection_mode(chat_win.contacts_list, GTK_SELECTION_NONE);
        gtk_stack_set_visible_child(chat_win.search_stack, 
                                    gtk_widget_get_parent(
                                        gtk_widget_get_parent(
                                            GTK_WIDGET(chat_win.search_list))));
        //sending search request
        chat->sys->login_substr = strdup(query);
        mx_user_search_by_substr_request(chat->sys, chat->json);
        free(chat->sys->login_substr);
        
        //Displaying search results
        get_search_results();
        cl_listener.fsearch = true;
    } 
    else { //User stopped searching
        gtk_list_box_set_selection_mode(chat_win.contacts_list, GTK_SELECTION_SINGLE);
        gtk_stack_set_visible_child(chat_win.search_stack, 
                                    gtk_widget_get_parent(
                                        gtk_widget_get_parent(
                                            GTK_WIDGET(chat_win.contacts_list))));

        cl_listener.fsearch = false;
    }
    printf("entry search finished\n");
}
static void get_search_results() {
    while (cl_listener.pending_requests[USER_SEARCH_BY_SUBSTRING]); //waiting to receive results
    int count = chat->sys->found_usernames_count;

    if (count) {
        GtkStyleContext *context_contact;
        if (chat_win.fresults)
            g_free(chat_win.fresults);
        chat_win.fresults = g_new(GtkWidget *, count);

        //mx_printstr("about to show results\n");
        for (int i = 0; i < count; i++) {
            chat_win.fresults[i] = gtk_label_new((const gchar *)chat->sys->found_usernames[i]);
            context_contact = gtk_widget_get_style_context(chat_win.fresults[i]);
            gtk_style_context_add_class(context_contact, "cont_list_search");
            gtk_container_add(GTK_CONTAINER(chat_win.search_list), chat_win.fresults[i]);
        }
        gtk_widget_show_all(GTK_WIDGET(chat_win.search_list));  
    }
    gtk_list_box_set_selection_mode(chat_win.search_list, GTK_SELECTION_SINGLE);
}
