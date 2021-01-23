#include "client.h"

extern t_chat_win chat_win;
extern t_client_st cl_listener;

static t_message *mb_form_msg(int user_id, char *msg_text, bool outgoing) {
    t_message *msg;

    msg = (t_message *) malloc(sizeof(t_message));
    msg->outgoing = outgoing;
    msg->user = user_id;
    msg->text = strdup(msg_text);
    msg->timestamp = 0;
    msg->next = NULL;
    return msg;
}
void on_chat_send_btn_clicked(GtkButton *btn, GtkBuilder *builder) {
    char *txt_msg = (char *)gtk_entry_get_text(chat_win.chat_msg);
    //mx_printstr("send button clicked\n");

    if (strlen(txt_msg) > 0) {
        //printf("%s\n", txt_msg);
        t_message *msg = mb_form_msg(cl_listener.contact_in_focus, txt_msg, true);
        mb_send_msg(msg);
        gtk_entry_set_text(chat_win.chat_msg, "");
    }
}
