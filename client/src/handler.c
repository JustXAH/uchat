// #include <gtk/gtk.h>
// #include <glib.h>
#include "client.h"

void send_msg(GtkButton *btn, GtkBuilder *builder) {
    GtkEntry *log_entry = GTK_ENTRY(gtk_builder_get_object
                                            (builder, "chat_msg_entry"));
    GtkLabel *err_label = GTK_LABEL(gtk_builder_get_object
                                            (builder, "error_lbl"));
    char *lbuffer = (char *)gtk_entry_get_text(log_entry);
    bool valid = true;
    if (strlen(lbuffer) < 6)
        valid = false;
    for (int i = 0; lbuffer[i]; i++) {
        if (!isdigit(lbuffer[i]) && !isalpha(lbuffer[i])) {
            valid = false;
        }
    }
    if (!valid) {
        printf("login type valid error\n");
        gtk_label_set_text(err_label,
                           "Invalid login or pass type \n [abc123][6ch min]\n");
        return;
    }
    gtk_label_set_text(err_label, "");
}

