#include "libmx.h"

void mx_bubble_sort(char **arr, int size) {
    char **tmp_arr = arr;
    char *tmp;

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (mx_strcmp(tmp_arr[j], tmp_arr[j + 1]) > 0) {
                tmp = tmp_arr[j + 1];
                tmp_arr[j + 1] = tmp_arr[j];
                tmp_arr[j] = tmp;
            }
        }
    }
    arr = tmp_arr;
}
