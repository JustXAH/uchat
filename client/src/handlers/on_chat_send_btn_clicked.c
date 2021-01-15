#include "client.h"

extern t_chat_win chat_win;



void on_chat_send_btn_clicked(GtkButton *btn, GtkBuilder *builder) {
    char *str_msg = (char *)gtk_entry_get_text(chat_win.chat_msg);
    mx_printstr("send button clicked\n");

    if (strlen(str_msg) > 0) {
        printf("%s\n", str_msg);    
        mb_display_msg(str_msg);
        gtk_entry_set_text(chat_win.chat_msg, "");
    }
    GtkWidget *view;
    GtkTextBuffer *buffer;

    view = gtk_text_view_new();
    buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(view));
    gtk_text_buffer_set_text (buffer, "test_contact", -1);

    gtk_container_add(GTK_CONTAINER(chat_win.contact_list), view);
    gtk_widget_show(view);
}
