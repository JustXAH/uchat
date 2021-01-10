//
// Created by Maksym Tsyfir on 1/5/21.
//

#include "client.h"
extern t_reg_win reg_win;
void destroy(GtkBuilder *builder) {
    gtk_main_quit();
}

void mx_gtk_window(int argc, char **argv, t_client *cli) {
    gtk_init(NULL, NULL);
    GError* error = NULL;

    cli->builder = gtk_builder_new();
    if (!gtk_builder_add_from_file(cli->builder, "glade/Login_and_reg.ui", &error)) {
        g_critical("error load file: %s", error->message);
        g_error_free(error);
        gtk_main_quit();
    }
   if (!gtk_builder_add_from_file(cli->builder, "glade/msg_test1.ui", &error)) {
        g_critical("error load file: %s", error->message);
        g_error_free(error);
        gtk_main_quit();
    }
    // подключаем сигналы
    gtk_builder_connect_signals(cli->builder, cli);

    cli->reg_window = GTK_WINDOW(gtk_builder_get_object(cli->builder, "log_and_reg_window"));
    if (cli->reg_window) {
        g_critical("error getting reg window");
        gtk_main_quit();
    }
    g_signal_connect(G_OBJECT(cli->reg_window),
                     "destroy", G_CALLBACK(destroy), cli->builder);

    cli->chat_window = GTK_WINDOW(gtk_builder_get_object(cli->builder, "msg_test"));
    if (cli->chat_window) {
        g_critical("error getting chat window");
        gtk_main_quit();
    }
    g_signal_connect(G_OBJECT(cli->chat_window),
                     "destroy", G_CALLBACK(destroy), cli->builder);

    gtk_widget_show(cli->reg_window);
    reg_win_init(cli);
    chat_win_init(cli);
    gtk_main();
//    cli->login = strdup(gtk_entry_get_text(GTK_ENTRY(gtk_builder_get_object(builder, "login_field"))));
}
void gtk_chat_window(t_client *cli) {
    gtk_widget_hide(cli->reg_window);
    gtk_widget_show(cli->chat_window);
    chat_win_init(cli);
}
