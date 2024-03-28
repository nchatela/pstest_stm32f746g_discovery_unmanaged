/* Copyright 2023 The MathWorks, Inc. */
#include "file.h"
volatile int b;
void function_time_2(void) {
    int i;
    for (i = 0; i < 20; i++) {
        b++;
    }
    function_time_4();
}

void function_time_4(void) {
    int i;
    for (i = 0; i < 20; i++) {
        b++;
    }
}