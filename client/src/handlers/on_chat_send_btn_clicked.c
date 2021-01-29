#include "client.h"

extern t_chat_win chat_win;
extern t_client_st cl_listener;
extern t_chat *chat;

static t_message *mb_form_msg(int chat_id,      int user_id,
                              char *user_name,  char *msg_text,
                              bool outgoing) {
    t_message *msg;

    msg = (t_message *) malloc(sizeof(t_message));
    msg->outgoing = true;
    msg->msg_id = 0;
    msg->chat_id = chat_id;
    msg->user_id = user_id;
    msg->user_name = mx_strdup(user_name);
    msg->text = mx_strdup(msg_text);
    msg->timestamp = NULL;
    msg->next = NULL;
    return msg;
}
void on_chat_send_btn_clicked(GtkButton *btn, GtkBuilder *builder) {
    if (cl_listener.vox_not_msg) {
        gtk_stack_set_visible_child(chat_win.msg_entry_stk, 
                                    GTK_WIDGET(chat_win.msg_entry_box));
        cl_listener.vox_not_msg = false;
        return;
    }
    char *txt_msg = (char *)gtk_entry_get_text(chat_win.msg_entry);

    if (strlen(txt_msg) > 0) {
        mx_add_message_request(chat->sys, chat->user, chat->json,
                               txt_msg, cl_listener.chat_in_focus, cl_listener.user_in_focus);

        gtk_entry_set_text(chat_win.msg_entry, "");
    }
}
