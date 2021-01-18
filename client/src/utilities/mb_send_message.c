#include "client.h"

extern t_contact_list *contact_list;
extern t_client_st cl_listener;

static void mb_add_msg_to_contact(t_message **history, t_message *new_msg) {
    if (*history == NULL) {
        *history = new_msg;
    } else {
        printf("prev msg exist in this dialog\n");
        t_message *temp = *history;

        while (temp->next) {
            printf("Proud Marry keeps on rolling %s\n", temp->text);
            temp = temp->next; 
        }
        temp->next = new_msg;
    }
    printf("this will be added to history: %s\n", (*history)->text);
    if (cl_listener.contact_in_focus == new_msg->user) {
        //needs proper msg forming
        //printf("message sent to the chat in focus\n");
        mb_display_msg(new_msg);
    }
}
void mb_send_msg(t_message *msg) {
    t_contact_list *temp = contact_list;

    if (temp && msg->user != 0) {
        do {
            if (temp->user_id == msg->user) {
                mb_add_msg_to_contact(&(temp->chat_history), msg);
                return;
            }
        } while ((temp = temp->next_contact));
    }
}
