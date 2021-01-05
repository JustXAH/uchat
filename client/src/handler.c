// #include <gtk/gtk.h>
// #include <glib.h>
#include "client.h"
static bool check_credentials(GtkEntry *log_entry, GtkEntry *pass_entry) {
    char *lbuffer = (char *)gtk_entry_get_text(log_entry);
    char *pbuffer = (char *)gtk_entry_get_text(pass_entry);
    bool valid = true;
    if (strlen(lbuffer) < 4 || strlen(pbuffer) < 6 )
        valid = false;
    for (int i = 0; lbuffer[i]; i++) {
        if (!isdigit(lbuffer[i]) && !isalpha(lbuffer[i]))
            valid = false;
    }
    return valid;
}
void login_btn_clicked_cb(GtkButton *btn, GtkBuilder *builder) {
    GtkEntry *log_entry = GTK_ENTRY(gtk_builder_get_object(builder, "login_field"));
    GtkEntry *pass_entry = GTK_ENTRY(gtk_builder_get_object(builder, "pass_field"));
    GtkLabel *err_label = GTK_LABEL(gtk_builder_get_object(builder, "login_label"));
    bool valid = check_credentials(log_entry, pass_entry);
    if (!valid) {
        printf("login type valid error\n");
        gtk_label_set_text(err_label, "Invalid login or pass");
        return;
    }
    gtk_label_set_text(err_label, "Success");
    //Send credentials to server
}

