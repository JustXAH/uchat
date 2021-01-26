#include "client.h"

extern t_chat_win chat_win;
extern t_client_st cl_listener;

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
    char *txt_msg = (char *)gtk_entry_get_text(chat_win.msg_entry);

    if (strlen(txt_msg) > 0) {
        //printf("%d\n", cl_listener.chat_in_focus);
        t_message *msg = mb_form_msg(cl_listener.chat_in_focus,
                                        cl_listener.my_id,
                                        cl_listener.my_name,
                                        txt_msg, 
                                        true);
        mb_send_msg(msg);
        gtk_entry_set_text(chat_win.msg_entry, "");
    }
}
