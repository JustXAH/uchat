#include "libmx.h"

char *mx_charjoin(char *str, char ch) {
    char *dst = NULL;
    int len = 0;

    if (str == NULL) {
        dst = mx_strnew(1);
        dst[0] = ch;
        return dst;
    }
    len = mx_strlen(str);
    dst = mx_strnew(len + 1);
    for (int i = 0; i <= len + 1; i++) {
        if (i == len + 1)
            dst[i] = ch;
        else
            dst[i] = str[i];
    }
    return dst;
}
