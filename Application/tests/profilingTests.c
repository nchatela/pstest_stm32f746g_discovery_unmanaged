/* Copyright 2023 The MathWorks, Inc. */
#include "file.h"
#include "pstunit.h"

PST_SUITE(suite_a);
PST_SUITE(suite_b);

PST_TEST(suite_a, t1) {
    int val = function_time_1();
    PST_ASSERT(val >= 0);
}

PST_TEST(suite_a, t3) {
    int val = function_time_3(3);
    PST_ASSERT(val == 9);

    val = function_time_3(-2);
    PST_ASSERT(val == -4);
}

PST_TEST(suite_b, t1) {
    int val = function_time_1();
    PST_ASSERT(val < 0);
}

PST_TEST(suite_b, t2) {
    int val = function_time_3(3);
    PST_ASSERT(val == 9);

    val = function_time_3(-2);
    PST_ASSERT(val == -4);
}


/* Registration function for this file (can be automatically generated) */
PST_REGFCN(registerTests) {
    PST_ADD_TEST(suite_a, t1);
    PST_ADD_TEST(suite_a, t3);
    PST_ADD_TEST(suite_b, t1);
    PST_ADD_TEST(suite_b, t2);

}
