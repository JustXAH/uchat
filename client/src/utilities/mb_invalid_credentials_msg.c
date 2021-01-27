#include "client.h"

extern t_reg_win reg_win;

void mb_invalid_credentials_msg() {
    gtk_label_set_text(reg_win.err_log_label, "Invalid login or pass");
}
void mb_reset_credentials_msg() {
    gtk_label_set_text(reg_win.err_log_label, "Login");
}
