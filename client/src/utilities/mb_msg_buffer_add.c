#include "client.h"

extern t_message *incoming_msg_buffer;
extern t_contact_list *contact_list;

static char *mb_get_user_name(int user_id) {
    t_contact_list *con_buff = contact_list;

    do {
        if (con_buff->user_id == user_id)
            return con_buff->user_name;
    } while ((con_buff = con_buff->next_contact));
    return NULL;
}
void mb_msg_buffer_add(int user_id, time_t time, char *msg_text) {
    if (incoming_msg_buffer == NULL) {
        incoming_msg_buffer = (t_message *)malloc(sizeof(t_message));
        incoming_msg_buffer->user = user_id;
        incoming_msg_buffer->user_name = mb_get_user_name(user_id);
        incoming_msg_buffer->timestamp = time;
        incoming_msg_buffer->text = msg_text;
        incoming_msg_buffer->outgoing = false;
        incoming_msg_buffer->next = NULL;

    } else {
        t_message *temp = incoming_msg_buffer;

        while (temp->next) 
            temp = temp->next;
        temp->next = (t_message *)malloc(sizeof(t_message));
        temp->next->id = user_id;
        temp->next->user_name = mb_get_user_name(user_id);
        temp->next->timestamp = time;
        temp->next->text = msg_text;
        temp->next->outgoing = false;
        temp->next->next = NULL;
    }
}