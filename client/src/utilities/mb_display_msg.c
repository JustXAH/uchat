#include "client.h"

extern t_chat_win chat_win;
extern t_client_st cl_listener;

void mb_display_msg(t_message *msg) {
//    char *txt_msg;
//    char *txt_buff;
    GtkWidget *view_name;
    GtkStyleContext *context_name;
//
//    txt_buff = mx_strjoin(msg->user_name, ": ");
//    txt_msg = mx_strjoin(txt_buff, msg->text);

    view_name = gtk_label_new(msg->user_name);
    context_name = gtk_widget_get_style_context(view_name);
    gtk_style_context_add_class(context_name, "msg_outext");
    gtk_label_set_xalign(GTK_LABEL(view_name), 1);

    gtk_container_add(GTK_CONTAINER(chat_win.msg_viewer), view_name);
    gtk_widget_show(view_name);

//    free(txt_msg);
//    free(txt_buff);
}

