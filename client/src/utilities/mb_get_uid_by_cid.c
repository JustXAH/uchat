#include "client.h"

extern t_chat_list *contact_list;

/*int mb_get_uid_by_cid(int chat_id) {
    t_chat_list *con_buf = contact_list;
    do
        if (con_buf->chat_id == chat_id)
            return con_buf->user_id;
    while ((con_buf = con_buf->next_contact));

    return -1;
}*/