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

int find_first_two_options();
int find_first_one_option();
int find_first_no_option();
int find_last_one_option();
int find_last_two_options();
int find_last_no_option();
int find_first_last_empty();
int binary_search_simple();
int binary_search_empty();
int binary_search_small();

int is_sorted_asc_simple();
int is_sorted_empty();
int is_sorted_asc_all_same();
int is_sorted_asc_false();
int is_sorted_desc_simple();
int is_sorted_desc_all_same();
int is_sorted_desc_false();

int is_unique_simple();
int is_unique_false();
int is_unique_empty();
int is_unique_all_same();
int get_unique_simple();
int get_unique_all_same();
int get_unique_already_unique();


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
        {"size_afterReserveResize", size_afterReserveResize},
        {"find_first_two_options", find_first_two_options},
        {"find_first_one_option", find_first_one_option},
        {"find_first_no_option", find_first_no_option},
        {"find_last_one_option", find_last_one_option},
        {"find_last_two_options", find_last_two_options},
        {"find_last_no_option", find_last_no_option},
        {"find_first_last_empty", find_first_last_empty},
        {"binary_search_simple", binary_search_simple},
        {"binary_search_empty", binary_search_empty},
        {"binary_search_small", binary_search_small},
        {"is_sorted_empty", is_sorted_empty},
        {"is_sorted_asc_simple", is_sorted_asc_simple},
        {"is_sorted_asc_all_same", is_sorted_asc_all_same},
        {"is_sorted_asc_false", is_sorted_asc_false},
        {"is_sorted_desc_simple", is_sorted_desc_simple},
        {"is_sorted_desc_all_same", is_sorted_desc_all_same},
        {"is_sorted_desc_false", is_sorted_desc_false},
        {"is_unique_simple", is_unique_simple},
        {"is_unique_false", is_unique_false},
        {"is_unique_empty", is_unique_empty},
        {"is_unique_all_same", is_unique_all_same},
        {"get_unique_simple", get_unique_simple},
        {"get_unique_all_same", get_unique_all_same},
        {"get_unique_already_unique", get_unique_already_unique}
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