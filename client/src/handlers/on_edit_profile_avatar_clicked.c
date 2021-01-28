//
// Created by Maksym Tsyfir on 1/28/21.
//


#include "client.h"

extern t_chat_win chat_win;
extern t_chat *chat;

static void err_msg() {
    gtk_window_set_transient_for(GTK_WINDOW(chat_win.err_pop), GTK_WINDOW(chat->sys->chat_window));
    gtk_widget_show_all((GTK_WIDGET(chat_win.err_pop)));

    gtk_label_set_text(GTK_LABEL(chat_win.err_msg_lbl), "Expeckt .jpg, .png, .jpeg, files!!!");
    int responce = gtk_dialog_run(GTK_DIALOG(GTK_WIDGET(chat_win.err_pop)));
    if (responce == 1) {
        gtk_widget_hide(GTK_WIDGET(chat_win.err_pop));
    } else {
        gtk_widget_hide(GTK_WIDGET(chat_win.err_pop));
    }
}

static bool credentieal_file_type(char *buffer) {
    char *extension = NULL;

    while (*buffer) {
        buffer++;
    }
    while (*buffer != '.') {
        buffer--;
    }
    extension = strdup(buffer);
    if(strcmp(extension, ".jpg") == 0 || strcmp(extension, ".png") == 0
       || strcmp(extension, ".jpeg") == 0) {
        free(extension);
        return true;
    }
    err_msg();
    free(extension);
    return false;
}

static void relize () {
    mx_printstr("\nFile path - ");
    mx_printstr(chat->sys->file_path);
    mx_printstr("\nFile name - ");
    mx_printstr(chat->sys->filename);
    mx_printstr("\n");
//    mx_strdel(&chat->sys->file_path);
//    mx_strdel(&chat->sys->voice_name);
//    mx_strdel(&chat->sys->filename);
}
static void get_filename() {
    char *buff_path = chat->sys->file_path;

    while (*buff_path) {
        buff_path++;
    }
    while (*buff_path != '/') {
        buff_path--;
    }
    buff_path++;
    chat->sys->filename = strdup(buff_path);
//    mx_save_voice_file_request(chat->sys, chat->user, chat->json);
}


static bool open_file_cooser() {
    char *buffer = NULL;

    gtk_widget_show_all(chat_win.file_choose_window);
    gtk_widget_get_can_default(chat_win.file_choose_window);

    // Check return value from Open Text File dialog box to see if user clicked the Open button
    if (gtk_dialog_run(GTK_DIALOG (chat_win.file_choose_window)) == 1) {
        // Get the file name from the dialog box
        buffer = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(chat_win.file_choose_window));
        if (buffer != NULL && credentieal_file_type(buffer)) {
            chat->sys->file_path = strdup(buffer);
            get_filename();
            free(buffer);
            gtk_widget_hide(chat_win.file_choose_window);
            return true;
        }
    }
    // Finished with the "Open Text File" dialog box, so hide it
    free(buffer);
    gtk_widget_hide(chat_win.file_choose_window);
    return false;

}

void on_edit_profile_avatar_clicked(GtkButton *btn) {
    if (open_file_cooser()) {
        relize();
    }
}
    //printf("settings button clicked\n");

