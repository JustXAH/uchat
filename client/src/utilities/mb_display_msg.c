#include "client.h"

extern t_chat_win chat_win;
extern t_client_st cl_listener;

void mb_display_msg(t_message *msg) {
    //mx_printstr("mb_display_msg");
    char *txt_msg;
    char *txt_buff;
    GtkWidget *view;

    txt_buff = mx_strjoin(msg->user_name, ": ");
    txt_msg = mx_strjoin(txt_buff, msg->text);

    view = gtk_label_new(txt_msg);
    gtk_label_set_xalign(GTK_LABEL(view), 0);

    gtk_container_add(GTK_CONTAINER(chat_win.msg_viewer), view);
    gtk_widget_show(view);

    free(txt_msg);
    free(txt_buff);
}
