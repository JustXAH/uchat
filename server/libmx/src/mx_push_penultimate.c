//
// Created by Dima Voichuck on 12/7/20.
//

#include "libmx.h"

void mx_push_penultimate(t_list **list, void *data) {
    t_list *back = mx_create_node(data);
    t_list *tmp = *list;
    t_list *tmp_3;
    t_list *tmp_4;

    if (*list == NULL || list == NULL) {
        *list = back;
        return;
    }
    if (tmp->next == NULL)
        mx_push_front(list, data);
    else {
        while (tmp->next != NULL) {
            tmp_3 = tmp;
            tmp = tmp->next;
            tmp_4 = tmp;
        }
        tmp_3->next = back;
        tmp_3 = tmp_3->next;
        tmp_3->next = tmp_4;
    }
}
