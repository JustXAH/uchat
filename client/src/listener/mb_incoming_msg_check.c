#include "client.h"

extern t_message *incoming_msg_buffer;
extern t_chat_list *contact_list;

static void delete_top_msg_in_buffer() {
    t_message *temp = incoming_msg_buffer->next;;

    free(incoming_msg_buffer->user_name);
    free(incoming_msg_buffer->text);
    free(incoming_msg_buffer->timestamp);
    free(incoming_msg_buffer);
    incoming_msg_buffer = temp;
}
void mb_incoming_msg_check() {
    t_chat_list * con_buf = contact_list;

    if (incoming_msg_buffer != NULL) {
        while (incoming_msg_buffer) {
            while (con_buf) {
                if (con_buf->chat_id == incoming_msg_buffer->chat_id) {
                    mb_add_msg_to_history(&(con_buf->chat_history),incoming_msg_buffer);
                }
                con_buf = con_buf->next_chat;
            }
            delete_top_msg_in_buffer();
        }
    }
}
