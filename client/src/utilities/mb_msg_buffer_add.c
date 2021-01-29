#include "client.h"

extern t_message *incoming_msg_buffer;
extern t_client_st cl_listener;
extern t_chat *chat;

static char *mb_get_user_name(int chat_id, int user_id) {
    for (int i = 0; i < chat->user->chats_count; i++)
        if (chat_id == chat->user->chats_id[i])
            return mx_strdup(chat->user->chats_name[i]);

    cl_listener.pending_requests[NEW_CHAT] = true;
    mx_add_new_chat_request(chat->sys, chat->user, chat->json, user_id);
    while (cl_listener.pending_requests[NEW_CHAT]);

    for (int i = 0; i < chat->user->chats_count; i++)
        if (chat_id == chat->user->chats_id[i])
            return mx_strdup(chat->user->chats_name[i]);
    return NULL;
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
            incoming_msg_buffer->user_name = mb_get_user_name(chat_id, user_id);
        if (incoming_msg_buffer->user_name == NULL)
            incoming_msg_buffer->user_name = mx_strdup(user_name);
    } 
    else {
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
            temp->next->user_name = mb_get_user_name(chat_id, user_id);
        if (temp->next->user_name == NULL)
            temp->next->user_name = mx_strdup(user_name);
    }
}
