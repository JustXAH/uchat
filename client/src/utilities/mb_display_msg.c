#include "client.h"

extern t_chat_win chat_win;

void mb_display_msg(char *msg_text) {
    GtkWidget *view;
    GtkTextBuffer *buffer;

    view = gtk_text_view_new();
    buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(view));
    gtk_text_buffer_set_text (buffer, msg_text, -1);

    gtk_container_add(GTK_CONTAINER(chat_win.chat_viewer), view);
    gtk_widget_show(view);
}