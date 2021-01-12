//
// Created by Dima Voichuck on 1/2/21.
//

#include "libmx.h"

bool mx_int_search(int *arr, int num) {
    for (int i = 0; arr[i]; i++){
        if (arr[i] == num)
            return true;
    }
    return false;
}
