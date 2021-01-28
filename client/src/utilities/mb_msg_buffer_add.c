#include "client.h"

extern t_message *incoming_msg_buffer;
extern t_chat_list *contact_list;
extern t_client_st cl_listener;

static char *mb_get_user_name(int chat_id) {
    t_chat_list *con_buff = contact_list;

    if (con_buff) {
        do {
           if (con_buff->chat_id == chat_id)
                return mx_strdup(con_buff->user_name);
        } while ((con_buff = con_buff->next_chat));
    }
    return NULL;
}
static int mb_get_uid_by_cid(int chat_id) {
    t_chat_list *con_buf = contact_list;
    do
        if (con_buf->chat_id == chat_id)
            return con_buf->user_id;
    while ((con_buf = con_buf->next_chat));

    return -1;
}
void mb_msg_buffer_add(int msg_id, int chat_id, int user_id, char *user_name, char *time, char *msg_text, bool outgoing) {
    if (incoming_msg_buffer == NULL) {
        incoming_msg_buffer = (t_message *)malloc(sizeof(t_message));
        incoming_msg_buffer->msg_id = msg_id;
        incoming_msg_buffer->chat_id = chat_id;
        incoming_msg_buffer->user_id = user_id;
        incoming_msg_buffer->timestamp = mx_strdup(time);
        incoming_msg_buffer->text = mx_strdup(msg_text);
        incoming_msg_buffer->outgoing = outgoing;
        incoming_msg_buffer->next = NULL;

        if (outgoing)
            incoming_msg_buffer->user_name = mx_strdup(cl_listener.my_name);
        else
            incoming_msg_buffer->user_name = mb_get_user_name(chat_id);
        if (incoming_msg_buffer->user_name == NULL)
            incoming_msg_buffer->user_name = mx_strdup(user_name);
    } else {
        t_message *temp = incoming_msg_buffer;

        while (temp->next) 
            temp = temp->next;
        temp->next = (t_message *)malloc(sizeof(t_message));
        temp->next->chat_id = chat_id;

        temp->next->msg_id = msg_id;
        temp->next->user_id = user_id;
        temp->next->user_name = mx_strdup(user_name);
        temp->next->timestamp = mx_strdup(time);
        temp->next->text = mx_strdup(msg_text);
        temp->next->outgoing = outgoing;
        temp->next->next = NULL;

        if (outgoing)
            temp->next->user_name = mx_strdup(cl_listener.my_name);
        else
            temp->next->user_name = mb_get_user_name(chat_id);
        if (temp->next->user_name == NULL)
            temp->next->user_name = mx_strdup(user_name);
    }
}
