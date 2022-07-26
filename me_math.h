#ifndef ME_MATH_H
#define ME_MATH_H

#include <stdarg.h>

int me_math_min_int(int n, ...) {
    int min = INT32_MAX;
    va_list arg_ptr;
    va_start(arg_ptr, n);
    for (int i = 0; i < n; i++) {
        int temp = va_arg(arg_ptr, int);
        if (temp < min) {
            min = temp;
        }
    }
    va_end(arg_ptr);
    return min;
}

int me_math_max_int(int n, ...) {
    int max = INT32_MIN;
    va_list arg_ptr;
    va_start(arg_ptr, n);
    for (int i = 0; i < n; i++) {
        int temp = va_arg(arg_ptr, int);
        if (temp > max) {
            max = temp;
        }
    }
    va_end(arg_ptr);
    return max;
}

#endif//ME_MATH_H
