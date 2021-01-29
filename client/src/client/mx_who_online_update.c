//
// Created by Igor Khanenko on 1/25/21.
//

#include "client.h"

extern t_chat_list *contact_list;

static void update_online_users_arr(t_user *user, cJSON *WHO_ONLINE,
                                    int max_users) {
    t_chat_list *con_buf;
    GtkStyleContext *context_contact;
    int users_online = 0;
    int friends_online = 0;
    int i;
    int j;

    for (i = 0; cJSON_GetArrayItem(WHO_ONLINE, i)->valueint != -1
        && i != max_users; i++) {
        users_online++;
        for (j = 0; j != user->contacts_count; j++) {

            if (cJSON_GetArrayItem(WHO_ONLINE, i)->valueint == user->contacts_id[j]) {
                friends_online++;
            }
        }
    }

    if (user->who_online != NULL)
        free(user->who_online);
    user->who_online = (int *) malloc(sizeof(int) * friends_online);
    user->who_online_count = 0;

    for (i = 0; i != users_online; i++) {
        for (j = 0; j != user->contacts_count; j++) {
            con_buf = contact_list;
            if (cJSON_GetArrayItem(WHO_ONLINE, i)->valueint == user->contacts_id[j]) {
                user->who_online[user->who_online_count++] = cJSON_GetArrayItem(
                        WHO_ONLINE, i)->valueint;
                while (con_buf) {
                    if (cJSON_GetArrayItem(WHO_ONLINE, i)->valueint ==  con_buf->user_id) {
                        con_buf->is_online = true;
                        context_contact = gtk_widget_get_style_context(con_buf->contact_gui);
                        if (con_buf->is_online)
                            gtk_style_context_add_class(context_contact, "cont_list_online");
                        else
                            gtk_style_context_add_class(context_contact, "cont_list_ofline");
                    }
                    con_buf= con_buf->next_chat;
                }
            }
        }
    }
}

void mx_who_online_update(t_system *sys, t_user *user, t_json *json) {
    json->WHO_ONLINE = cJSON_GetObjectItemCaseSensitive(json->SERVER_JSON,
                                                        "WHO_ONLINE");

    if (MALLOC_SIZE(user->who_online)) {
        free(user->who_online);
    }
    if (user->contacts_count > 0) {
        update_online_users_arr(user, json->WHO_ONLINE,
                                cJSON_GetArraySize(json->WHO_ONLINE));
    }
    cJSON_DeleteItemFromObject(json->SERVER_JSON, "WHO_ONLINE");
}
