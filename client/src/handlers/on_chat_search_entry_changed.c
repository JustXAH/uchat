#include "client.h"

extern t_chat_win chat_win;
extern t_chat_list *contact_list;
extern t_client_st cl_listener;

void on_chat_search_entry_changed() {
    //printf("search entry changed\n"); 
    // char *query = (char *)gtk_entry_get_text(GTK_ENTRY(chat_win.fsearch_entry));
    // t_chat_list *con_buf = contact_list;
    // do {
    //     if (!mx_count_substr(con_buf->user_name, query) && strlen(query) > 0)
    //         gtk_widget_hide(con_buf->contact_gui);
    //     else
    //         gtk_widget_show(con_buf->contact_gui);
    // } while ((con_buf = con_buf->next_chat));
    //gtk_list_store_clear(GTK_LIST_STORE(chat_win.s_comp_model));
    //get_search_results();
}
/* Creates a tree model containing the completions */
