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

int get_intersection_basic();
int get_intersection_none();
int get_intersection_left_empty();
int get_intersection_both_empty();
int get_intersection_with_duplicates();
int get_intersection_identical();
int get_intersection_null_args();
int get_intersection_unsorted_input();
int get_intersection_descending();

int get_union_basic();
int get_union_left_empty();
int get_union_both_empty();
int get_union_with_duplicates();
int get_union_identical();
int get_union_null_args();
int get_union_unsorted_input();
int get_union_descending();

int sort_empty();
int sort_single();
int sort_reverse();
int sort_with_duplicates();
int sort_random_small();
int sort_all_equal();

int range_simple_forward();
int range_forward_step_two();
int range_backward();
int range_backward_step_two();
int range_empty();
int range_zero_step();
int range_invalid_negative_step_forward();
int range_stop_exclusive();
int range_null_self();

int reverse_basic();


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
        {"get_unique_already_unique", get_unique_already_unique},
        {"get_intersection_basic", get_intersection_basic},
        {"get_intersection_none", get_intersection_none},
        {"get_intersection_left_empty", get_intersection_left_empty},
        {"get_intersection_both_empty", get_intersection_both_empty},
        {"get_intersection_with_duplicates", get_intersection_with_duplicates},
        {"get_intersection_identical", get_intersection_identical},
        {"get_intersection_null_args", get_intersection_null_args},
        {"get_intersection_unsorted_input", get_intersection_unsorted_input},
        {"get_intersection_descending", get_intersection_descending},
        {"get_union_basic", get_union_basic},
        {"get_union_left_empty", get_union_left_empty},
        {"get_union_both_empty", get_union_both_empty},
        {"get_union_with_duplicates", get_union_with_duplicates},
        {"get_union_identical", get_union_identical},
        {"get_union_null_args", get_union_null_args},
        {"get_union_unsorted_input", get_union_unsorted_input},
        {"get_union_descending", get_union_descending},
        {"sort_empty", sort_empty},
        {"sort_single", sort_single},
        {"sort_reverse", sort_reverse},
        {"sort_with_duplicates", sort_with_duplicates},
        {"sort_random_small", sort_random_small},
        {"sort_all_equal", sort_all_equal},
        {"range_simple_forward", range_simple_forward},
        {"range_forward_step_two", range_forward_step_two},
        {"range_backward", range_backward},
        {"range_backward_step_two", range_backward_step_two},
        {"range_empty", range_empty},
        {"range_zero_step", range_zero_step},
        {"range_invalid_negative_step_forward", range_invalid_negative_step_forward},
        {"range_stop_exclusive", range_stop_exclusive},
        {"range_null_self", range_null_self},
        {"reverse_basic", reverse_basic},
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