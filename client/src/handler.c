// #include <gtk/gtk.h>
// #include <glib.h>
#include "../inc/client.h"

void send_msg(GtkButton *btn, GtkBuilder *builder) {
    GtkLabel *err_label = GTK_LABEL(gtk_builder_get_object
                                   (builder, "msg_text"));
    gtk_label_set_text(err_label,
                            "HELLO");
}
