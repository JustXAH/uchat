//#include <gtk/gtk.h>
//#include <glib.h>
#include "client.h"

void destroy(GtkBuilder *builder) {
    gtk_main_quit();
}

int main(int argc, char *argv[]) {
    gtk_init(NULL, NULL);
    GtkBuilder *builder;
    GtkWindow *window;
    GError* error = NULL;

    builder = gtk_builder_new();
    if (!gtk_builder_add_from_file(builder, "PointG.ui", &error)) {
        g_critical("error load file: %s", error->message);
        g_error_free(error);
        gtk_main_quit();
    }
    gtk_builder_connect_signals(builder, builder);
    window = GTK_WINDOW(gtk_builder_get_object(builder, "login_window"));
    if (window) {
        g_critical("error getting window");
        gtk_main_quit();
    }
    
    g_signal_connect(G_OBJECT(window),
                                "destroy", G_CALLBACK(destroy), builder);
    gtk_widget_show(window);
    gtk_main();
}
