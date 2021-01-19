#include "client.h"

extern t_chat_win chat_win;

void mb_display_msg(t_message *msg) {
    char *txt_msg;
    char *txt_buff;
    GtkWidget *view;
    GtkTextBuffer *buffer;

    //txt_buff = mx_strjoin(msg->timestamp, msg->user);
    txt_buff = mx_itoa(msg->user);
    txt_msg = mx_strjoin(txt_buff, msg->text);
    view = gtk_text_view_new();
    buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(view));
    gtk_text_buffer_set_text(buffer, txt_msg, -1);
    gtk_container_add(GTK_CONTAINER(chat_win.chat_viewer), view);
    gtk_widget_show(view);
    free(txt_msg);
    free(txt_buff);
}
