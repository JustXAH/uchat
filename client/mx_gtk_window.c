//
// Created by Maksym Tsyfir on 1/5/21.
//

#include "client.h"

void destroy(GtkBuilder *builder) {
    gtk_main_quit();
}

void mx_gtk_window(int argc, char **argv, t_client *cli) {
    gtk_init(NULL, NULL);
    GError* error = NULL;

    cli->builder = gtk_builder_new();
    if (!gtk_builder_add_from_file(cli->builder, "PointG.ui", &error)) {
        g_critical("error load file: %s", error->message);
        g_error_free(error);
        gtk_main_quit();
    }
    // подключаем сигналы
    gtk_builder_connect_signals(cli->builder, cli);
    cli->window = GTK_WINDOW(gtk_builder_get_object(cli->builder, "login_window"));
    if (cli->window) {
        g_critical("error getting window");
        gtk_main_quit();
    }

    g_signal_connect(G_OBJECT(cli->window),
                     "destroy", G_CALLBACK(destroy), cli->builder);
    gtk_widget_show(cli->window);
    gtk_main();
//    cli->login = strdup(gtk_entry_get_text(GTK_ENTRY(gtk_builder_get_object(builder, "login_field"))));
}
