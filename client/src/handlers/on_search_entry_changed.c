#include "client.h"

extern t_chat_win chat_win;

static void get_search_results();
void on_search_entry_changed() {
    //printf("search entry changed\n"); 
    char *query = (char *)gtk_entry_get_text(GTK_ENTRY(chat_win.search_entry));
    
    gtk_list_store_clear(GTK_LIST_STORE(chat_win.s_comp_model));
    get_search_results();
                
}
/* Creates a tree model containing the completions */
static void get_search_results() {
    GtkTreeIter iter;
    gtk_list_store_append (GTK_LIST_STORE(chat_win.s_comp_model), &iter);
    gtk_list_store_set (GTK_LIST_STORE(chat_win.s_comp_model), &iter, 0, "GNOME", -1);
    gtk_list_store_append (GTK_LIST_STORE(chat_win.s_comp_model), &iter);
    gtk_list_store_set (GTK_LIST_STORE(chat_win.s_comp_model), &iter, 0, "Horsecock", -1);
    gtk_list_store_append (GTK_LIST_STORE(chat_win.s_comp_model), &iter);
    gtk_list_store_set (GTK_LIST_STORE(chat_win.s_comp_model), &iter, 0, "Ckif", -1);
    gtk_list_store_append (GTK_LIST_STORE(chat_win.s_comp_model), &iter);
    gtk_list_store_set (GTK_LIST_STORE(chat_win.s_comp_model), &iter, 0, "Count", -1);
    gtk_list_store_append (GTK_LIST_STORE(chat_win.s_comp_model), &iter);
    gtk_list_store_set (GTK_LIST_STORE(chat_win.s_comp_model), &iter, 0, "Cunt", -1);
}