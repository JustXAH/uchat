#include "libmx.h"

void *mx_realloc(void *ptr, size_t size) {
    unsigned char *new_pointer = NULL;
    size_t len = 0;
    if  (__APPLE__)
        len = malloc_size(ptr);
    else
        return NULL;
    if ((int)size >= 0) {
        if (size != 0 && len > size)
            return ptr;
        new_pointer = malloc(size);
        if (size != 0 && ptr != NULL)
            new_pointer = mx_memcpy(new_pointer, ptr, size);
        free(ptr);
    }
    return new_pointer;
}
