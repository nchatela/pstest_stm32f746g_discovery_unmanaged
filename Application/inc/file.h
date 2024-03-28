/* Copyright 2022 The MathWorks, Inc. */
extern int function_time_1(void);
extern int function_time_3(int a);
extern int function_recursive(int val);
extern void function_time_2(void);
extern void function_time_4(void);
static void function_time_5(void);
static void function_time_6(void);


#ifdef _WIN32
#define INLINE inline
#else
#define INLINE __inline__
#endif
static int d = 0;
INLINE static void function_time_5(void) {
    int i;
    for (i = 0; i < 20; i++) {
        d++;
    }
    function_time_6();
}

INLINE static void function_time_6(void) {
    int i;
    for (i = 0; i < 20; i++) {
        d++;
    }
}
