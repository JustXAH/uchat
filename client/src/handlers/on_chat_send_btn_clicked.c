#include "client.h"

extern t_chat_win chat_win;
extern t_client_st cl_listener;

static t_msg *mb_form_msg(int user_id, char *msg_text, bool outgoing) {
    t_msg *msg;

    msg = (t_msg *) malloc(sizeof(t_msg));
    msg->outgoing = outgoing;
    msg->user_id = user_id;
    msg->msg_text = strdup(msg_text);
    msg->msg_time = NULL;
    msg->next_msg = NULL;
    return msg;
}
void on_chat_send_btn_clicked(GtkButton *btn, GtkBuilder *builder) {
    char *txt_msg = (char *)gtk_entry_get_text(chat_win.chat_msg);
    //mx_printstr("send button clicked\n");

    if (strlen(txt_msg) > 0) {
        //printf("%s\n", txt_msg);
        t_msg *msg = mb_form_msg(cl_listener.contact_in_focus, txt_msg, true);
        mb_send_msg(msg);
        gtk_entry_set_text(chat_win.chat_msg, "");
    }
}
