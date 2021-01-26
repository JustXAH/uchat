#include "client.h"

extern t_chat_list *contact_list;
extern t_client_st cl_listener;

void mb_send_msg(t_message *msg) {
    t_chat_list *temp = contact_list;

    if (temp && msg->chat_id != 0) {
        do {
            if (temp->chat_id == msg->chat_id) {
                mb_add_msg_to_history(&(temp->chat_history), msg);
                return;
            }
        } while ((temp = temp->next_chat));
    }
}
