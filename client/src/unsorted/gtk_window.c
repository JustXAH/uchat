//
// Created by Maksym Tsyfir on 1/5/21.
//

#include "client.h"

extern t_reg_win reg_win;

void destroy(GtkBuilder *builder) {
    gtk_main_quit();
}

void gtk_log_window(t_chat *chat) {
    gtk_init(NULL, NULL);
    GError* error = NULL;

    chat->sys->builder = gtk_builder_new();
    if (!gtk_builder_add_from_file(chat->sys->builder, "glade/Login_and_reg.ui", &error)) {
        g_critical("error load file: %s", error->message);
        g_error_free(error);
        gtk_main_quit();
    }

    // подключаем сигналы
    gtk_builder_connect_signals(chat->sys->builder, chat->sys);

    chat->sys->reg_window = GTK_WINDOW(gtk_builder_get_object(chat->sys->builder, "log_and_reg_window"));
    if (!chat->sys->reg_window) {
        g_critical("error getting reg window");
        gtk_main_quit();
    }
    g_signal_connect(G_OBJECT(chat->sys->reg_window),
                     "destroy", G_CALLBACK(destroy), chat->sys->builder);

    gtk_widget_show(GTK_WIDGET(chat->sys->reg_window));
    reg_win_init(chat->sys);
    printf("zhopa\n");
    gtk_main();
    printf("zhopa1\n");
}
void gtk_chat_window(t_chat *chat) {
    mx_printstr("t1\n");
    gtk_main_quit();
    mx_printstr("t2\n");
    GError* error = NULL;

    if (!gtk_builder_add_from_file(chat->sys->builder, "glade/msg_test1.ui", &error)) {
        g_critical("error load file: %s", error->message);
        g_error_free(error);
        gtk_main_quit();
    }
    gtk_builder_connect_signals(chat->sys->builder, chat->sys);
    chat->sys->chat_window = GTK_WINDOW(gtk_builder_get_object(chat->sys->builder, "msg_test"));
    if (!chat->sys->chat_window) {
        g_critical("error getting chat window");
        gtk_main_quit();
    }
    g_signal_connect(G_OBJECT(chat->sys->chat_window),
                     "destroy", G_CALLBACK(destroy), chat->sys->builder);
    gtk_widget_show(GTK_WIDGET(chat->sys->chat_window));
    mx_printstr("t3\n");
    gtk_widget_hide(GTK_WIDGET(chat->sys->reg_window));
    chat_win_init(chat->sys);
    gtk_main();
    mx_printstr("t4\n");
}