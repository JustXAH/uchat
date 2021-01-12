//
// Created by Maksym Tsyfir on 1/5/21.
//

#include "client.h"

extern t_reg_win reg_win;

void destroy(GtkBuilder *builder) {
    gtk_main_quit();
}

void mx_gtk_window(t_system *sys, t_user *user) {
    gtk_init(NULL, NULL);
    GError* error = NULL;

    sys->builder = gtk_builder_new();
    if (!gtk_builder_add_from_file(sys->builder, "glade/Login_and_reg.ui", &error)) {
        g_critical("error load file: %s", error->message);
        g_error_free(error);
        gtk_main_quit();
    }

    // подключаем сигналы
    gtk_builder_connect_signals(sys->builder, sys);

    sys->reg_window = GTK_WINDOW(gtk_builder_get_object(sys->builder, "log_and_reg_window"));
    if (sys->reg_window) {
        g_critical("error getting reg window");
        gtk_main_quit();
    }
    g_signal_connect(G_OBJECT(sys->reg_window),
                     "destroy", G_CALLBACK(destroy), sys->builder);

    gtk_widget_show(GTK_WIDGET(sys->reg_window));
    reg_win_init(sys);
    chat_win_init(sys);
    gtk_main();
}
void gtk_chat_window(t_system *sys, t_user *user) {
    gtk_main_quit();
    gtk_widget_destroy(GTK_WIDGET(sys->reg_window));
    GError* error = NULL;

    if (!gtk_builder_add_from_file(sys->builder, "glade/msg_test1.ui", &error)) {
        g_critical("error load file: %s", error->message);
        g_error_free(error);
        gtk_main_quit();
    }
    //gtk_builder_connect_signals(cli->builder, cli);
    sys->chat_window = GTK_WINDOW(gtk_builder_get_object(sys->builder, "msg_test"));
    if (sys->chat_window) {
        g_critical("error getting chat window");
        gtk_main_quit();
    }
    g_signal_connect(G_OBJECT(sys->chat_window),
                     "destroy", G_CALLBACK(destroy), sys->builder);
    gtk_widget_show(GTK_WIDGET(sys->chat_window));
    chat_win_init(sys);
    gtk_main();
}