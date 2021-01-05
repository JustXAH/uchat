#include "client.h"


void send_msg(GtkButton *btn, GtkBuilder *builder) {
    GtkEntry *chat_msg = GTK_ENTRY(gtk_builder_get_object
                                            (builder, "chat_msg_entry"));
    GtkListBox *chat_viewer = GTK_LABEL(gtk_builder_get_object
                                            (builder, "chat_msg_lst_box"));
    char *str_msg = (char *)gtk_entry_get_text(log_entry);

    if (strlen(str_msg) > 0) {
        gtk_entry_set_text(chat_msg, "");

    }
}