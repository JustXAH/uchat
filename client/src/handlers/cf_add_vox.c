//
// Created by Maksym Tsyfir on 1/26/21.
//

#include "client.h"

extern t_chat_win chat_win;
extern t_chat *chat;

static void relize () {
    mx_printstr("\nVoice name - ");
  mx_printint(chat->sys->position);
    mx_printstr("\nFile path - ");
    mx_printstr(chat->sys->file_path);
    mx_printstr("\nVoice name - ");
    mx_printstr(chat->sys->voice_name);
    mx_printstr("\n");
    mx_strdel(&chat->sys->file_path);
    mx_strdel(&chat->sys->voice_name);
}
static void parsing () {
    int i = strlen(chat->sys->file_path);
    char *buff = NULL;

    for (; chat->sys->file_path[i] != '.'; i--);

}

static void open_file_cooser(int i) {

    // Show the "Open Text File" dialog box
    gtk_widget_show(chat_win.file_choose_window);

    // Check return value from Open Text File dialog box to see if user clicked the Open button
    if (gtk_dialog_run(GTK_DIALOG (chat_win.file_choose_window)) == GTK_RESPONSE_OK) {
        // Get the file name from the dialog box
       chat->sys->file_path = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(chat_win.file_choose_window));
        if (chat->sys->file_path != NULL) {
            chat->sys->position = i;

        }
    }

    // Finished with the "Open Text File" dialog box, so hide it
    gtk_widget_hide(chat_win.file_choose_window);
}

void on_edit_vax1_open_btn_clicked (GtkButton *btn) {
    open_file_cooser(0);
    chat->sys->voice_name = (char *)gtk_entry_get_text(chat_win.edit_vax1_entry);
    relize ();
}
void on_edit_vax2_open_btn_clicked (GtkButton *btn) {
    open_file_cooser(1);
    chat->sys->voice_name = (char *)gtk_entry_get_text(chat_win.edit_vax2_entry);
    relize ();
}
void on_edit_vax3_open_btn_clicked (GtkButton *btn) {
    open_file_cooser(2);
    chat->sys->voice_name = (char *)gtk_entry_get_text(chat_win.edit_vax3_entry);
    relize ();
}
void on_edit_vax4_open_btn_clicked (GtkButton *btn) {
    open_file_cooser(3);
    chat->sys->voice_name = (char *)gtk_entry_get_text(chat_win.edit_vax4_entry);
    relize ();
}
void on_edit_vax5_open_btn_clicked (GtkButton *btn) {
    open_file_cooser(4);
    chat->sys->voice_name = (char *)gtk_entry_get_text(chat_win.edit_vax5_entry);
    relize ();
}
void on_edit_vax6_open_btn_clicked (GtkButton *btn) {
    open_file_cooser(5);
    chat->sys->voice_name = (char *)gtk_entry_get_text(chat_win.edit_vax6_entry);
    relize ();
}
void on_edit_vax7_open_btn_clicked (GtkButton *btn) {
    open_file_cooser(6);
    chat->sys->voice_name = (char *)gtk_entry_get_text(chat_win.edit_vax7_entry);
    relize ();
}
void on_edit_vax8_open_btn_clicked (GtkButton *btn) {
    open_file_cooser(7);
    chat->sys->voice_name = (char *)gtk_entry_get_text(chat_win.edit_vax8_entry);
    relize ();
}



// File --> Quit
void on_menuitm_quit_activate(GtkMenuItem *menuitem, GtkBuilder *builder)
{
    gtk_main_quit();
}

