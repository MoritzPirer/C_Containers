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

int destroy_initialized();
int destroy_NULL();
int destroy_double();


int size_empty();
int size_push_pop();
int size_afterErase();
int size_afterPartialErase();
int size_afterReserveResize();

typedef struct _Test_ {
    const char* m_name;
    int (*test_function)(void);
} Test;

bool runTest(Test test) {
    printf("\033[0m\nRunning test '%s'...\n", test.m_name);

    int return_value = test.test_function();
    
    if (return_value == 0) {
        printf("\033[32m[PASS] test '%s' correctly returned %d\n", test.m_name, return_value);
        return true;
    }
    else {
        printf("\033[31m[FAIL] test '%s' returned %d\n",
            test.m_name, return_value);
        return false;
    }
}

void testrunner() {
    Test tests[] = {
        {"init_elementSize_0", init_elementSize_0},
        {"init_NULL", init_NULL},
        {"init_size_0",init_size_0},
        {"init_size_1", init_size_1},
        {"init_size_pow2", init_size_pow2},
        {"init_size_XL", init_size_XL},
        {"init_size_XXXL", init_size_XXXL},
        {"destroy_initialized", destroy_initialized},
        {"destroy_NULL", destroy_NULL},
        {"destroy_double", destroy_double},
        {"size_empty", size_empty},
        {"size_push_pop", size_push_pop},
        {"size_afterErase", size_afterErase},
        {"size_afterPartialErase", size_afterPartialErase},
        {"size_afterReserveResize", size_afterReserveResize}
    };

    size_t total = sizeof(tests) / sizeof(Test);
    size_t passed = 0;

    for (size_t i = 0; i < total; i++) {
        passed += runTest(tests[i]);
    }

    printf("\033[0m\n%zu/%zu tests passed\n", passed, total);

    if (passed != total) {
        printf("\033[31m\nWARNING! SOME TESTS FAILED!\n");
    }
    else {
        printf("\033[32m\nALL TESTS PASSED!\n");
    }
   
}