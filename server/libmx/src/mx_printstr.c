#include "libmx.h"

void mx_printstr(const char *s) {
    s ? write (1, s, mx_strlen(s)) : write(1, "(null)", 6);
}
