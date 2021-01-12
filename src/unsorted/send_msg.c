#include "client.h"

extern t_chat_win chat_win;

static void AddListItem(char *msg_text)
{
    GtkWidget *view;
    GtkTextBuffer *buffer;

    view = gtk_text_view_new();
    buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(view));
    gtk_text_buffer_set_text (buffer, msg_text, -1);

    gtk_container_add(GTK_CONTAINER(chat_win.chat_viewer), view);
    /*
    item = gtk_list_item_new_with_label (sText);

    gtk_signal_connect (GTK_OBJECT (item), "select",
            GTK_SIGNAL_FUNC (listitem_selected), sText);

    gtk_container_add (GTK_CONTAINER (listbox), item);
*/
    gtk_widget_show(view);
}

void send_msg(GtkButton *btn, GtkBuilder *builder) {
    char *str_msg = (char *)gtk_entry_get_text(chat_win.chat_msg);

    if (strlen(str_msg) > 0) {
        printf("%s\n", str_msg);
        
        AddListItem(str_msg);
        gtk_entry_set_text(chat_win.chat_msg, "");
    }
}
