#include "libmx.h"

void mx_int_bubble_sort_reverse(int *arr, int size) {
    int *tmp_arr = arr;
    int tmp;

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (tmp_arr[j] < tmp_arr[j + 1]) {
                tmp = tmp_arr[j + 1];
                tmp_arr[j + 1] = tmp_arr[j];
                tmp_arr[j] = tmp;
            }
        }
    }
    arr = tmp_arr;
}
