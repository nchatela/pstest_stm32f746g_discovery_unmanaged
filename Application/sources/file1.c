/* Copyright 2023 The MathWorks, Inc. */
extern volatile int b;
#include "file.h"
int function_time_1(void) {
    int val = 0, i;
    for (i = 0; i < 20; i++) {
        b++;
    }
    function_time_2();
    function_time_5();

    val = function_recursive(10);
    return val;
}

int function_time_3(int a) {
    function_time_2();
    function_time_5();
    if (a < 0) {
        return a * 2;
    } else if (a > 0) {
        return a * 3;
    }

    if ((a != 0) && (b != 0)) {
    	a++;
    }
    return a;
}

int function_recursive (int val) {
    if (val > 1) {
        return (2 * function_recursive(val - 1));
    } else {
        return val;
    }
}
