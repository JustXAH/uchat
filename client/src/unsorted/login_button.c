// #include <gtk/gtk.h>
// #include <glib.h>
#include "client.h"

extern t_reg_win reg_win;
extern t_chat *chat;

static bool check_credentials();
void on_log_login_btn_clicked(GtkButton *btn) {
    bool valid = check_credentials();
    if (!valid) {
        printf("login type valid error\n");
        /*gtk_widget_override_color(reg_win.err_log_label,
                                   GTK_STATE_FLAG_NORMAL,
                                   "#7F7F7F");*/
        gtk_label_set_text(reg_win.err_log_label, "Invalid login or pass");
        return;
    }
    chat->user->login = strdup(gtk_entry_get_text(reg_win.log_entry));
    chat->user->password = strdup(gtk_entry_get_text(reg_win.pass_entry));
    printf("\nLOGIN = %s\nPASS = %s\n", chat->user->login, chat->user->password);
    gtk_label_set_text(reg_win.err_log_label, "Success");
    gtk_label_set_text(reg_win.err_pas_label, "Success");

    mx_registration_or_login_request(chat->sys, chat->user);
    //gtk_chat_window(sys, user);
}
static bool check_credentials() {
    char *lbuffer = (char *)gtk_entry_get_text(reg_win.log_entry);
    char *pbuffer = (char *)gtk_entry_get_text(reg_win.pass_entry);
    bool valid = true;
    if (strlen(lbuffer) < 4 || strlen(pbuffer) < 2 )
        valid = false;
    for (int i = 0; lbuffer[i]; i++) {
        if (!isdigit(lbuffer[i]) && !isalpha(lbuffer[i]))
            valid = false;
    }
    return valid;
}
/////////////////////////////////////////////////////////////////////////////////////