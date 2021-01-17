#include "client.h"

extern t_msg *incoming_msg_buffer;
extern t_contact_list *contact_list;

static char *mb_get_user_name(int user_id) {
    t_contact_list *con_buff = contact_list;

    do {
        if (con_buff->user_id == user_id)
            return con_buff->user_name;
    } while ((con_buff = con_buff->next_contact));
    return NULL;
}
void mb_msg_buffer_add(int user_id, char *time, char *msg_text) {
    if (incoming_msg_buffer == NULL) {
        incoming_msg_buffer = (t_msg *)malloc(sizeof(t_msg));
        incoming_msg_buffer->user_id = user_id;
        incoming_msg_buffer->user_name = mb_get_user_name(user_id);
        incoming_msg_buffer->msg_time = time;
        incoming_msg_buffer->msg_text = msg_text;
        incoming_msg_buffer->outgoing = false;
        incoming_msg_buffer->next_msg = NULL;

    } else {
        t_msg *temp = incoming_msg_buffer;

        while (temp->next_msg) 
            temp = temp->next_msg;
        temp->next_msg = (t_msg *)malloc(sizeof(t_msg));
        temp->next_msg->user_id = user_id;
        temp->next_msg->user_name = mb_get_user_name(user_id);
        temp->next_msg->msg_time = time;
        temp->next_msg->msg_text = msg_text;
        temp->next_msg->outgoing = false;
        temp->next_msg->next_msg = NULL;
    }
}
