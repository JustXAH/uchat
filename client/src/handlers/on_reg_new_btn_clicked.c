#include "client.h"

extern t_client_st cl_listener;
extern t_reg_win reg_win;
extern t_chat *chat;

void on_log_reg_btn_clicked(GtkButton *btn, t_system *sys) {
    mb_reset_credentials_msg();
    printf("Start REG\n");
    if (sys->builder) {
        gtk_stack_set_visible_child_name(reg_win.stk, "reg_window");
    }
}//--------------------------------------------------------------------------------//
void on_back_to_log_clicked(GtkButton *btn, t_system *sys) {
    printf("back to log\n");
    if (sys->builder) {
        gtk_stack_set_visible_child_name(reg_win.stk, "log_window");
    }
}//--------------------------------------------------------------------------------//
static void change_lbls(GtkEntry *reg_pas_label1, GtkEntry *reg_pas_label2, char *text);
static bool check_pass_valid();
static bool check_valid_login();
static bool check_valid_email();
void on_reg_new_btn_clicked(GtkButton *btn) {
    bool valid = true;

    if (!check_valid_login()) {
        printf("Login = %s\n", (char *)gtk_entry_get_text(reg_win.reg_log));
        valid = false;
    }
    if (!check_pass_valid()) {
        printf("Pass1 = %s\n", (char *)gtk_entry_get_text(reg_win.reg_pass1));
        printf("Pass2 = %s\n", (char *)gtk_entry_get_text(reg_win.reg_pass2));
        valid = false;
    }
//    if (!check_valid_email())
//        valid = false;
    if (valid == false)
        return;
    chat->user->login = strdup((char *)gtk_entry_get_text(reg_win.reg_log));
    chat->user->password = strdup((char *)gtk_entry_get_text(reg_win.reg_pass1));
    chat->user->hash_password = g_compute_checksum_for_string(G_CHECKSUM_SHA256,
                                                         chat->user->password,
                                                         strlen(chat->user->password));
    mx_strdel(&chat->user->password);
    //printf("1LOGIN = %s\n1PASS = %s\n", user->login, user->password);
    chat->sys->reg_request = true;
    cl_listener.my_name = strdup(gtk_entry_get_text(reg_win.reg_log));
    mx_registration_or_login_request(chat->sys, chat->user, chat->json);
    //Send credentials to server
}
static void change_lbls(GtkEntry *reg_pas_label1, GtkEntry *reg_pas_label2, char *text){
    printf("%s\n", text);
    gtk_label_set_text(GTK_LABEL(reg_pas_label1), text);
    gtk_label_set_text(GTK_LABEL(reg_pas_label2), text);
    /*gtk_widget_override_color (reg_pas_label1,
                               GTK_STATE_FLAG_NORMAL,
                               "#7F7F7F");*/
}
static bool check_pass_valid() {
    char *pass1 = (char *)gtk_entry_get_text(reg_win.reg_pass1);
    char *pass2 = (char *)gtk_entry_get_text(reg_win.reg_pass2);
    bool valid = true;

    if(strcmp(pass1, pass2) != 0) {
        gtk_label_set_text(reg_win.reg_pas_label1, "Passwords do not match");
        gtk_label_set_text(reg_win.reg_pas_label2, "Passwords do not match");
         return false;
    }
    if (strlen(pass1) < 1 ) {
        gtk_label_set_text(reg_win.reg_pas_label1, "Password is less than 6 chars");
        gtk_label_set_text(reg_win.reg_pas_label2, "Password is less than 6 chars");
        return false;
    }
    printf("Passwords are OK\n");
    gtk_label_set_text(reg_win.reg_pas_label1, "Password is OK");
    gtk_label_set_text(reg_win.reg_pas_label2, "Confirmation matches");
    return true;
}
static bool check_valid_login() {
    char *lbuffer = (char *)gtk_entry_get_text(reg_win.reg_log);

    if (lbuffer[0] == '\0') {
        printf("%s\n", "Login field is empty");
        gtk_label_set_text(reg_win.reg_log_label, "Login field is empty");
        return false;
    }
    if (strlen(lbuffer) < 4) {
        printf("%s\n", "Login is less 4 char");
        gtk_label_set_text(reg_win.reg_log_label, "Login is less 4 char");
        return false;
    }
    else if (strlen(lbuffer) > 17) {
        printf("%s\n", "Login is more 16 char");
        gtk_label_set_text(reg_win.reg_log_label, "Login is more 16 char");
        return false;
    }
    for (int i = 0; lbuffer[i]; i++) {
        if (!isdigit(lbuffer[i]) && !isalpha(lbuffer[i])){
            printf("%s\n", "Login contains illegal chars");
            gtk_label_set_text(reg_win.reg_log_label, "Login contains illegal chars");
            return false;
        }
    }
    printf("Login is OK\n");
    //gtk_label_set_text(reg_win.reg_log_label, "Login is OK");
    return true;
}
/*
static bool check_valid_email() {
    char *ebuffer = (char *)gtk_entry_get_text(reg_win.reg_email);

    for(int i = 0; ebuffer[i]; i++) {
        if (ebuffer[i] == '@') {
            for (int j = i + 1; ebuffer[j]; j++) {
                if (ebuffer[j] == '.') {
                    printf("%s\n", "E-mail is OK");
                    gtk_label_set_text(reg_win.reg_email_label, "E-mail is OK");
                    return true;
                }
                else if (!isalpha(ebuffer[j]) && !isdigit(ebuffer[j])) {
                    printf("E-mail \"%s\" is incorrect\n", ebuffer);
                    gtk_label_set_text(reg_win.reg_email_label, "E-mail is incorrect");
                    return false;
                }
            }
        }
        else if (!isalpha(ebuffer[i]) && !isdigit(ebuffer[i]) && ebuffer[i] != '.'){
            printf("E-mail \"%s\" is incorrect\n", ebuffer);
            gtk_label_set_text(reg_win.reg_email_label, "E-mail is incorrect");
            return false;
        }
    }
    printf("E-mail is incorrect\n");
    gtk_label_set_text(reg_win.reg_email_label, "E-mail is incorrect");
    return false;
}
*/
////////////////////////////////////////////////////////////////////////////////////
