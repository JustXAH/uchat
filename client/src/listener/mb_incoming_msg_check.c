#include "client.h"

extern t_message *incoming_msg_buffer;
extern t_chat_list *contact_list;
extern t_client_st cl_listener;
extern t_message *chat_history;

static void delete_top_msg_in_buffer() {
    t_message *temp = incoming_msg_buffer->next;;

    free(incoming_msg_buffer->user_name);
    free(incoming_msg_buffer->text);
    free(incoming_msg_buffer->timestamp);
    free(incoming_msg_buffer);
    incoming_msg_buffer = temp;
}
static void mb_add_msg_to_history(t_message **history, t_message *new_msg) {
    mx_printstr("mb_add_msg_to_his\n");
    if (*history == NULL) {
        *history = new_msg;
    } else {
        t_message *temp = *history;

        while (temp->next && temp->next->msg_id < new_msg->chat_id)
            temp = temp->next; 

        new_msg->next = temp->next;
        temp->next = new_msg;
    }
    mx_printstr("mb_add_msg_to_his 2\n");
    mb_display_msg(new_msg);
}
void mb_incoming_msg_check() {
    t_chat_list * con_buf = contact_list;
    //mx_printstr("mb_incoming_msg_check\n");
    if (incoming_msg_buffer != NULL) {
            mx_printstr("mb_incoming_msg_check if1\n");
        while (incoming_msg_buffer) {
             mx_printstr("mb_incoming_msg_check while\n");
            if (cl_listener.chat_in_focus == incoming_msg_buffer->chat_id)
                mb_add_msg_to_history(&(chat_history), incoming_msg_buffer);
            delete_top_msg_in_buffer();
        }
    }

}
