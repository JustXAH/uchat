#include "client.h"

extern t_chat_win chat_win;
extern t_client_st cl_listener;

void mb_display_msg(t_message *msg) {
//    char *txt_msg;
//    char *txt_buff;
    GtkWidget *msg_box;
    GtkStyleContext *context_box;
    GtkWidget *view_name;
    GtkStyleContext *context_name;
    GtkWidget *view_msg;
    GtkStyleContext *context_msg;
//
//    txt_buff = mx_strjoin(msg->user_name, ": ");
//    txt_msg = mx_strjoin(txt_buff, msg->text);

    view_name = gtk_label_new(msg->user_name);
    context_name = gtk_widget_get_style_context(view_name);
    gtk_style_context_add_class(context_name, "msg_outext");
    gtk_label_set_xalign(GTK_LABEL(view_name), 1);

    view_msg = gtk_label_new(msg->text);
    context_msg = gtk_widget_get_style_context(view_msg);
    gtk_style_context_add_class(context_msg, "msg_intext");
    gtk_label_set_xalign(GTK_LABEL(view_msg), 1);

    msg_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    context_box = gtk_widget_get_style_context(msg_box);
    gtk_style_context_add_class(context_box, "msg_box");

    gtk_box_pack_start(GTK_BOX(msg_box), view_name, TRUE, TRUE, 5);
    gtk_box_pack_end(GTK_BOX(msg_box), view_msg, TRUE, TRUE, 5);

    gtk_container_add(GTK_CONTAINER(chat_win.msg_viewer), msg_box);
    gtk_widget_show_all(msg_box);

//    free(txt_msg);
//    free(txt_buff);
}
