//
// Created by Maksym Tsyfir on 1/5/21.
//

#include "client.h"

extern t_chat *chat;
extern t_reg_win reg_win;

void destroy(GtkBuilder *builder) {
    chat->sys->exit = 1;
    printf("EXIT = TRUE\n");
    gtk_main_quit();
}

void gtk_window_initializtion(t_chat *chat) {
    gtk_init(NULL, NULL);
    GError* error = NULL;

    GtkCssProvider *cssProvider = gtk_css_provider_new ();
    gtk_css_provider_load_from_path(cssProvider,"glade/style.css",NULL);
    gtk_style_context_add_provider_for_screen(gdk_screen_get_default(), GTK_STYLE_PROVIDER(cssProvider), GTK_STYLE_PROVIDER_PRIORITY_USER);
    chat->sys->builder = gtk_builder_new();
    if (!gtk_builder_add_from_file(chat->sys->builder, "glade/Login_and_reg.ui", &error)) {
        g_critical("error load file: %s", error->message);
        g_error_free(error);
        gtk_main_quit();
    }
    // подключаем сигналы
    gtk_builder_connect_signals(chat->sys->builder, chat->sys);

    chat->sys->reg_window = GTK_WINDOW(gtk_builder_get_object(chat->sys->builder, "log_and_reg_window"));
    chat->sys->chat_window = GTK_WINDOW(gtk_builder_get_object(chat->sys->builder, "msg_test"));
    if (!chat->sys->reg_window) {
        g_critical("error getting reg window");
        gtk_main_quit();
    }
    g_signal_connect(G_OBJECT(chat->sys->reg_window), "destroy", G_CALLBACK(destroy), chat->sys->builder);
    g_signal_connect(G_OBJECT(chat->sys->chat_window),"destroy", G_CALLBACK(destroy), chat->sys);

    gtk_widget_show(GTK_WIDGET(chat->sys->reg_window));

    mb_client_globals_initialization();
    reg_win_init(chat->sys);
    chat_win_init(chat->sys);
    mx_printstr("gtk_main_starting\n");
    gtk_main();
}
void gtk_show_chat_window(t_chat *chat) {
    gtk_widget_hide(GTK_WIDGET(chat->sys->reg_window));
    gtk_widget_show_all(GTK_WIDGET(chat->sys->chat_window));
}
void gtk_show_log_window(t_chat *chat) {
    gtk_widget_hide(GTK_WIDGET(chat->sys->chat_window));
    gtk_widget_show_all(GTK_WIDGET(chat->sys->reg_window));
}


