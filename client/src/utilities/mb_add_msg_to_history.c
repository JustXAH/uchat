#include "client.h"

extern t_chat_list *contact_list;
extern t_client_st cl_listener;

void mb_add_msg_to_history(t_message **history, t_message *new_msg) {
    if (*history == NULL) {
        *history = new_msg;
    } else {
        t_message *temp = *history;

        while (temp->next)
            temp = temp->next; 
        temp->next = new_msg;
    }
    if (cl_listener.chat_in_focus == new_msg->chat_id)
        mb_display_msg(new_msg);
}
