//
// Created by Maksym Tsyfir on 1/26/21.
//

#include "client.h"

extern t_chat_win chat_win;
extern t_chat *chat;


static void err_msg() {
    gtk_window_set_transient_for(GTK_WINDOW(chat_win.err_pop), GTK_WINDOW(chat->sys->chat_window));
    gtk_widget_show_all(GTK_WIDGET(chat_win.err_pop));

    gtk_label_set_text(GTK_LABEL(chat_win.err_msg_lbl), "Expeckt .wav, .mp3, .aif, .mid files!!!");
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
    if(strcmp(extension, ".wav") == 0 || strcmp(extension, ".mp3") == 0
       || strcmp(extension, ".aif") == 0 || strcmp(extension, ".mid") == 0) {
        free(extension);
        return true;
    }
    free(extension);
    return false;
}

static void relize () {
    mx_printstr("\nVoice path - ");
    mx_printint(chat->sys->position);
    mx_printstr("\nFile path - ");
    mx_printstr(chat->sys->file_path);
    mx_printstr("\nVoice name - ");
    mx_printstr(chat->sys->voice_name);
    mx_printstr("\nFile name - ");
    mx_printstr(chat->sys->filename);
    mx_printstr("\n");

    // запрос на сохранение голосового файла в БД и на сервере
    mx_save_voice_file_request(chat->sys, chat->user, chat->json);

//    mx_save_voice_file_request(chat->sys, chat->user, chat->json);
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
}

static bool open_file_cooser(int i) {
    char *buffer = NULL;
    // Show the "Open Text File" dialog box
//    gtk_window_set_transient_for(GTK_WINDOW(chat_win.file_choose_window), GTK_WINDOW(chat->sys->chat_window));
    gtk_widget_show_all(chat_win.file_choose_window);
    gtk_widget_get_can_default(chat_win.file_choose_window);

    // Check return value from Open Text File dialog box to see if user clicked the Open button
    if (gtk_dialog_run(GTK_DIALOG (chat_win.file_choose_window)) == 1) {
        // Get the file name from the dialog box
        buffer = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(chat_win.file_choose_window));
        if (buffer != NULL && credentieal_file_type(buffer)) {
            chat->sys->file_path = strdup(buffer);
            chat->sys->position = i;
            get_filename();
            free(buffer);
            gtk_widget_hide(chat_win.file_choose_window);
            return true;
        }
    }
    // Finished with the "Open Text File" dialog box, so hide it
    err_msg();
    free(buffer);
    gtk_widget_hide(chat_win.file_choose_window);
    return false;

}

void on_edit_vax1_open_btn_clicked (GtkButton *btn) {
    if (open_file_cooser(0)) {
        chat->sys->voice_name = strdup(gtk_entry_get_text(chat_win.edit_vax1_entry));
        if(strcmp(chat->sys->voice_name, "") == 0)
            chat->sys->voice_name = strdup("Vox 1");
        relize();
    }
}
void on_edit_vax2_open_btn_clicked (GtkButton *btn) {
    if (open_file_cooser(1)) {
        chat->sys->voice_name = strdup(gtk_entry_get_text(chat_win.edit_vax2_entry));
        if(strcmp(chat->sys->voice_name, "") == 0)
            chat->sys->voice_name = strdup("Vox 2");
        relize();
    }
}
void on_edit_vax3_open_btn_clicked (GtkButton *btn) {
    if (open_file_cooser(2)) {
        chat->sys->voice_name = strdup(gtk_entry_get_text(chat_win.edit_vax3_entry));
        if(strcmp(chat->sys->voice_name, "") == 0)
            chat->sys->voice_name = strdup("Vox 3");
        relize();
    }
}
void on_edit_vax4_open_btn_clicked (GtkButton *btn) {
    if (open_file_cooser(3)) {
        chat->sys->voice_name = strdup(gtk_entry_get_text(chat_win.edit_vax4_entry));
        if(strcmp(chat->sys->voice_name, "") == 0)
            chat->sys->voice_name = strdup("Vox 4");
        relize();
    }
}
void on_edit_vax5_open_btn_clicked (GtkButton *btn) {
    if (open_file_cooser(4)) {
        chat->sys->voice_name = strdup(gtk_entry_get_text(chat_win.edit_vax5_entry));
        if(strcmp(chat->sys->voice_name, "") == 0)
            chat->sys->voice_name = strdup("Vox 5");
        relize();
    }
}
void on_edit_vax6_open_btn_clicked (GtkButton *btn) {
    if (open_file_cooser(5)) {
        chat->sys->voice_name = strdup(gtk_entry_get_text(chat_win.edit_vax6_entry));
        if(strcmp(chat->sys->voice_name, "") == 0)
            chat->sys->voice_name = strdup("Vox 6");
        relize();
    }
}
void on_edit_vax7_open_btn_clicked (GtkButton *btn) {
    if (open_file_cooser(6)) {
        chat->sys->voice_name = strdup(gtk_entry_get_text(chat_win.edit_vax7_entry));
        if(strcmp(chat->sys->voice_name, "") == 0)
            chat->sys->voice_name = strdup("Vox 7");
        relize();
    }
}
void on_edit_vax8_open_btn_clicked (GtkButton *btn) {
    if (open_file_cooser(7)) {
        chat->sys->voice_name = strdup(gtk_entry_get_text(chat_win.edit_vax8_entry));
        if(strcmp(chat->sys->voice_name, "") == 0)
            chat->sys->voice_name = strdup("Vox 8");
        relize();
    }
}
