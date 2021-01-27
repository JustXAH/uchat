#include "client.h"

extern t_chat_win chat_win;

gboolean on_search_entry_focus_out(GtkWidget *widget, GdkEvent  *event, gpointer   user_data) {
    
    //g_object_unref(chat_win.s_comp_model);
    return true;
}