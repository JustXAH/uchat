#include "libmx.h"

int mx_int_len(int num) {
    int len;

    for (len = 1; num /= 10; len++);
    return len;
}
