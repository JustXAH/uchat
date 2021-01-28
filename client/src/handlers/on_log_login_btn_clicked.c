// #include <gtk/gtk.h>
// #include <glib.h>
#include "client.h"

extern t_client_st cl_listener;
extern t_reg_win reg_win;
extern t_chat *chat;

static bool check_credentials();
void on_log_login_btn_clicked(GtkButton *btn) {
    bool valid = check_credentials();
    if (!valid) {
        printf("login type valid error\n");
        gtk_label_set_text(reg_win.err_log_label,
                           "Lambert, Lambert what a prick\n");
        //mb_invalid_credentials_msg();
        return;
    }
    chat->user->login = strdup(gtk_entry_get_text(reg_win.log_entry));
    chat->user->password = strdup(gtk_entry_get_text(reg_win.pass_entry));

    chat->user->hash_password= g_compute_checksum_for_string(G_CHECKSUM_SHA256,
                                                         chat->user->password,
                                                         strlen(chat->user->password));
    mx_strdel(&chat->user->password);

    printf("\nsent LOGIN = %s\nsent PASS = %s\n", chat->user->login,
           chat->user->password);
    cl_listener.my_name = strdup(gtk_entry_get_text(reg_win.log_entry));
    cl_listener.logged_in = 2;
    gtk_stack_set_visible_child_name(reg_win.stk, "loading_log_window");
    mx_registration_or_login_request(chat->sys, chat->user, chat->json);
}
static bool check_credentials() {
    char *lbuffer = (char *)gtk_entry_get_text(reg_win.log_entry);
    char *pbuffer = (char *)gtk_entry_get_text(reg_win.pass_entry);
    bool valid = true;
    if (strlen(lbuffer) < 3 || strlen(pbuffer) < 1 )
        valid = false;
    for (int i = 0; lbuffer[i]; i++) {
        if (!isdigit(lbuffer[i]) && !isalpha(lbuffer[i]))
            valid = false;
    }
    return valid;
}
/////////////////////////////////////////////////////////////////////////////////////
