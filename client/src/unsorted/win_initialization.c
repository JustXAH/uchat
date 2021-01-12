#include "client.h"

t_reg_win reg_win;
t_chat_win chat_win;

void reg_win_init(t_system *sys) {
    reg_win.log_entry = GTK_ENTRY(gtk_builder_get_object(sys->builder,
                                                        "log_login_field"));
    reg_win.pass_entry = GTK_ENTRY(gtk_builder_get_object(sys->builder,
                                                        "log_pass_field"));
    reg_win.err_log_label = GTK_LABEL(gtk_builder_get_object(sys->builder,
                                                        "log_login_lable"));
    reg_win.err_pas_label = GTK_LABEL(gtk_builder_get_object(sys->builder,
                                                        "log_pass_lable"));
    reg_win.stk = GTK_STACK(gtk_builder_get_object(sys->builder,
                                                        "autoriz_stack"));
    reg_win.reg_log = GTK_ENTRY(gtk_builder_get_object(sys->builder,
                                                        "reg_login_field"));
    reg_win.reg_pass1 = GTK_ENTRY(gtk_builder_get_object(sys->builder,
                                                        "reg_pass_field"));
    reg_win.reg_pass2 = GTK_ENTRY(gtk_builder_get_object(sys->builder,
                                                        "reg_pass_check_field"));
    reg_win.reg_email = GTK_ENTRY(gtk_builder_get_object(sys->builder,
                                                        "reg_email_field"));
    reg_win.reg_log_label = GTK_LABEL(gtk_builder_get_object(sys->builder,
                                                        "reg_login_lable"));
    reg_win.reg_pas_label1 = GTK_LABEL(gtk_builder_get_object(sys->builder,
                                                        "reg_pass_lable"));
    reg_win.reg_pas_label2 = GTK_LABEL(gtk_builder_get_object(sys->builder,
                                                        "reg_pass_conf_lable"));
    reg_win.reg_email_label = GTK_LABEL(gtk_builder_get_object(sys->builder,
                                                        "reg_email_lable"));
}
void chat_win_init(t_system *sys) {
    chat_win.chat_msg = GTK_WIDGET(gtk_builder_get_object(sys->builder,
                                                        "chat_msg_entry"));
    chat_win.chat_viewer = GTK_WIDGET(gtk_builder_get_object(sys->builder,
                                                        "chat_msg_lst_box"));
 
}
