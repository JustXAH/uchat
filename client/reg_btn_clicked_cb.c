//
// Created by Maksym Tsyfir on 1/5/21.
//

#include "client.h"

void destroy(GtkBuilder *builder) {
    gtk_main_quit();
}
//bool check_credentials(GtkEntry *log_entry, GtkEntry *pass_entry) {
//    char *lbuffer = (char *)gtk_entry_get_text(log_entry);
//    char *pbuffer = (char *)gtk_entry_get_text(pass_entry);
//    bool valid = true;
//    if (strlen(lbuffer) < 4 || strlen(pbuffer) < 6 )
//        valid = false;
//    for (int i = 0; lbuffer[i]; i++) {
//        if (!isdigit(lbuffer[i]) && !isalpha(lbuffer[i]))
//            valid = false;
//    }
//    return valid;
//}
void reg_btn_clicked_cb(GtkButton *btn, t_client *cli) {
    gtk_init(NULL, NULL);
    GError* error = NULL;

    cli->builder = gtk_builder_new();
    if (!gtk_builder_add_from_file(cli->builder, "Register.ui", &error)) {
        g_critical("error load file: %s", error->message);
        g_error_free(error);
        gtk_main_quit();
    }
    // подключаем сигналы
    gtk_builder_connect_signals(cli->builder, cli);
//    gtk_widget_hide(cli->window);
    g_signal_connect(G_OBJECT(cli->window),
                     "destroy", G_CALLBACK(destroy), cli->builder);
    cli->window = GTK_WINDOW(gtk_builder_get_object(cli->builder, "register_window"));
    if (!cli->window) {
        g_critical("error getting window");
        gtk_main_quit();
    }
    gtk_widget_show(cli->window);

//    GtkEntry *log_entry = GTK_ENTRY(gtk_builder_get_object(cli->builder, "login_field"));
//    GtkEntry *pass_entry = GTK_ENTRY(gtk_builder_get_object(cli->builder, "pass_field"));
//    GtkLabel *err_label = GTK_LABEL(gtk_builder_get_object(cli->builder, "login_label"));
//    bool valid = check_credentials(log_entry, pass_entry);
//    if (!valid) {
//        printf("login type valid error\n");
//        gtk_widget_override_color (err_label,
//                                   GTK_STATE_FLAG_NORMAL,
//                                   "#7F7F7F");
//        gtk_label_set_text(err_label, "Invalid login or pass");
//        return;
//    }
//    cli->login = strdup(gtk_entry_get_text(log_entry));
//    cli->password = strdup(gtk_entry_get_text(pass_entry));
//    gtk_label_set_text(err_label, "Success");
//    //Send credentials to server
}