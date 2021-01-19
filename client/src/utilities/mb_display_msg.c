#include "client.h"

extern t_chat_win chat_win;

void mb_display_msg(t_msg *msg) {
    char *txt_msg;
    char *txt_buff;
    GtkWidget *view;
    GtkTextBuffer *buffer;

    txt_buff = mx_strjoin(msg->msg_time, msg->user_name);
    txt_msg = mx_strjoin(txt_buff, msg->msg_text);
    view = gtk_text_view_new();
    buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(view));
    gtk_text_buffer_set_text(buffer, txt_msg, -1);
    gtk_container_add(GTK_CONTAINER(chat_win.chat_viewer), view);
    gtk_widget_show(view);
    free(txt_msg);
    free(txt_buff);
}
