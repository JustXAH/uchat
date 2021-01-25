#include "libmx.h"

char *mx_strjoin_ush(char const *s1, char const *s2) {
    char *join;

    if (s1 == NULL && s2 == NULL)
        return NULL;
    else if (s1 == NULL) {
        join = mx_strnew(mx_strlen(s2) + 1);
        join = mx_strcat(join, "/");
        join = mx_strcat(join, s2);
        return join;
    }
    else if (s2 == NULL)
        return mx_strdup(s1);
    else {
        join = mx_strnew(mx_s_strlen(s1) + 1 + mx_s_strlen(s2));
        join = mx_strcat(mx_strcpy(join, s1), "/");
        join = mx_strcat(join, s2);
        return join;
    }
}
