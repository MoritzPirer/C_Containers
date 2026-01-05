#include <stdio.h>
#include <string.h>
#include <stdbool.h>

//forward declare test fucntions here
int init_elementSize_0();
int init_NULL();
int init_size_0();
int init_size_1();
int init_size_pow2();
int init_size_XL();
int init_size_XXXL();

typedef struct _Test_ {
    const char* m_name;
    int (*test_function)(void);
    int expected_return;
} Test;

bool runTest(Test test) {
    printf("\033[0m\nRunning test '%s'...\n", test.m_name);

    int return_value = test.test_function();
    
    if (return_value == test.expected_return) {
        printf("\033[32m[PASS] test '%s' correctly returned %d\n", test.m_name, return_value);
        return true;
    }
    else {
        printf("\033[31m[FAIL] test '%s' returned %d instead of expected value %d\n",
            test.m_name, return_value, test.expected_return);
        return false;
    }
}

void testrunner() {
    Test tests[] = {
        {"init_elementSize_0", init_elementSize_0, 0},
        {"init_NULL", init_NULL, 0},
        {"init_size_0",init_size_0, 0},
        {"init_size_1", init_size_1, 0},
        {"init_size_pow2", init_size_pow2, 0},
        {"init_size_XL", init_size_XL, 0},
        {"init_size_XXXL", init_size_XXXL, 0}
    };

    size_t total = sizeof(tests) / sizeof(Test);
    size_t passed = 0;

    for (size_t i = 0; i < total; i++) {
        passed += runTest(tests[i]);
    }

    printf("\n%zu/%zu tests passed\n", passed, total);

    if (passed != total) {
        printf("\nWARNING! SOME TESTS FAILED\n");
    }
   
}