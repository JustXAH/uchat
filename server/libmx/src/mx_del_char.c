//
// Created by Dima Voichuck on 11/24/20.
//

#include "libmx.h"

void mx_del_char(char *str, int id, char ch) {
    if (id != 0 && str[id] == ch)
        str[id] = '\0';
}
