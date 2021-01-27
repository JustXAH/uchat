//
// Created by Dima Voichuck on 11/3/20.
//

#include "libmx.h"

char *mx_substr(const char *str, int a, int b) {
    char *tmp;
    int j = 0;
    if (a == b) {
        tmp = mx_strnew(1);
        tmp[0] = str[a];
    }
    else {
        tmp = mx_strnew(b - a + 1);
        for (int i = a; i < b && str[i] != '\0'; i++) {
            tmp[j] = str[i];
            j++;
        }
    }
    return tmp;
}
