//
// Created by Maksym Tsyfir on 1/26/21.
//

#include "client.h"

extern t_chat_win chat_win;
extern t_chat *chat;

static void open_file_cooser() {
//    gchar *filename = NULL;        // Name of file to open from dialog box
    gchar *file_path = NULL;        // Name of file to open from dialog box
//    gchar *file_contents = NULL;    // For reading contents of file
//    gboolean file_success = FALSE;  // File read status

    // Show the "Open Text File" dialog box
    gtk_widget_show(chat_win.file_choose_window);

    // Check return value from Open Text File dialog box to see if user clicked the Open button
    if (gtk_dialog_run(GTK_DIALOG (chat_win.file_choose_window)) == GTK_RESPONSE_OK) {
        // Get the file name from the dialog box
//        filename = gtk_file_chooser_get_current_name(GTK_FILE_CHOOSER(chat_win.file_choose_window));
       chat->sys->file_path = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(chat_win.file_choose_window));
        if (chat->sys->file_path != NULL) {
            printf("\n%s\n", chat->sys->file_path);
//            printf("\n%s\n", filename);
//            g_free(filename);
            g_free(chat->sys->file_path);
        }
    }

    // Finished with the "Open Text File" dialog box, so hide it
    gtk_widget_hide(chat_win.file_choose_window);
}

void on_edit_vax1_open_btn_clicked (GtkButton *btn) {
    open_file_cooser();
}



// File --> Quit
void on_menuitm_quit_activate(GtkMenuItem *menuitem, GtkBuilder *builder)
{
    gtk_main_quit();
}

