#include "libmx.h"

void mx_printchar_error(char c) {
    write (2, &c, 1);
}
