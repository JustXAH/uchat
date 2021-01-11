// #include <gtk/gtk.h>
// #include <glib.h>
#include "client.h"

extern t_reg_win reg_win;

bool check_credentials() {
    char *lbuffer = (char *)gtk_entry_get_text(reg_win.log_entry);
    char *pbuffer = (char *)gtk_entry_get_text(reg_win.pass_entry);
    bool valid = true;
    if (strlen(lbuffer) < 4 || strlen(pbuffer) < 6 )
        valid = false;
    for (int i = 0; lbuffer[i]; i++) {
        if (!isdigit(lbuffer[i]) && !isalpha(lbuffer[i]))
            valid = false;
    }
    return valid;
}
void on_log_login_btn_clicked(GtkButton *btn, t_system *sys, t_user *user) {
   bool valid = check_credentials();
    if (!valid) {
        printf("login type valid error\n");
        gtk_widget_override_color (reg_win.err_log_label,
                                   GTK_STATE_FLAG_NORMAL,
                                   "#7F7F7F");
        gtk_widget_override_color (reg_win.err_pas_label,
                                   GTK_STATE_FLAG_NORMAL,
                                   "#7F7F7F");
        gtk_label_set_text(reg_win.err_log_label, "Invalid login or pass");
        return;
    }
    user->login = strdup(gtk_entry_get_text(reg_win.log_entry));
    user->password = strdup(gtk_entry_get_text(reg_win.pass_entry));
    printf("\nLOGIN = %s\nPASS = %s\n", user->login, user->password);
    gtk_label_set_text(reg_win.err_log_label, "Success");
    gtk_label_set_text(reg_win.err_pas_label, "Success");

//    gtk_chat_window(sys, user);
    mx_registration_or_login_request(sys, user);
}

void on_log_reg_btn_clicked(GtkButton *btn, t_system *sys) {
    printf("Start REG\n");
    if (sys->builder) {
        gtk_stack_set_visible_child_name(reg_win.stk, "reg_window");
    }
}

void on_back_to_log_clicked(GtkButton *btn, t_system *sys) {
    printf("back to log\n");
    if (sys->builder) {
        gtk_stack_set_visible_child_name(reg_win.stk, "log_window");
    }
}

static void change_lbls(GtkEntry *reg_pas_label1, GtkEntry *reg_pas_label2, char *text){
    printf("%s\n", text);
    gtk_label_set_text(reg_pas_label1, text);
    gtk_label_set_text(reg_pas_label2, text);
    gtk_widget_override_color (reg_pas_label1,
                               GTK_STATE_FLAG_NORMAL,
                               "#7F7F7F");
}
static bool check_pass_valid(){
    char *pass1 = (char *)gtk_entry_get_text(reg_win.reg_pass1);
    char *pass2 = (char *)gtk_entry_get_text(reg_win.reg_pass2);
    bool valid = true;

    if(strcmp(pass1, pass2) != 0) {
        change_lbls(reg_win.reg_pas_label1, reg_win.reg_pas_label2, "Passwords do not match");
        return false;
    }
    if (strlen(pass1) < 6 ) {
        change_lbls(reg_win.reg_pas_label1, reg_win.reg_pas_label2, "Passwords less 6 chars");
        return false;
    }
    for (int i = 0; pass1[i]; i++) {
        if (!isdigit(pass1[i]) && !isalpha(pass1[i])) {
            change_lbls(reg_win.reg_pas_label1, reg_win.reg_pas_label2, "App just char and sym");
            return false;
        }
    }
    printf("Passwords are OK");
    gtk_label_set_text(reg_win.reg_pas_label1, "Password is OK");
    gtk_label_set_text(reg_win.reg_pas_label2, "Confirmation matched");
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
            printf("%s\n", "App just char and sym");
            gtk_label_set_text(reg_win.reg_log_label, "App just char and sym");
            return false;
        }
    }
    printf("%s\n", "Login is OK");
    gtk_label_set_text(reg_win.reg_log_label, "Login is OK");
    return true;
}

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
                    printf("E-mail \"%s\" is incorrect\n", ebuffer[i]);
                    gtk_label_set_text(reg_win.reg_email_label, "E-mail is incorrect");
                    return false;
                }
            }
        }
        else if (!isalpha(ebuffer[i]) && !isdigit(ebuffer[i]) && ebuffer[i] != '.'){
            printf("E-mail \"%s\" is incorrect\n", ebuffer[i]);
            gtk_label_set_text(reg_win.reg_email_label, "E-mail is incorrect");
            return false;
        }
    }
    printf("%s\n", "E-mail is incorrect");
    gtk_label_set_text(reg_win.reg_email_label, "E-mail is incorrect");
    return false;
}

void on_reg_new_btn_clicked(GtkButton *btn, t_system *sys, t_user *user) {
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
    sys->registration = true;
    mx_registration_or_login_request(sys, user);


//    cli->login = strdup(gtk_entry_get_text(log_entry));
//    cli->password = strdup(gtk_entry_get_text(pass_entry));
//    printf("\nLOGIN = %s\nPASS = %s\n", cli->login, cli->password);
//    gtk_label_set_text(err_log_label, "Success");
//    gtk_label_set_text(err_pas_label, "Success");
    //Send credentials to server
}
