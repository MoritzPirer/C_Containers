#include "tests.h"

int tests_run = 0;
int tests_failed = 0;

void vec_tests();
void vec_algs_tests();
void hset_tests();

int main(void) {
    printf("=== STARTING ALL LIBRARY TESTS ===\n\n");

    vec_tests();
    vec_algs_tests();
    hset_tests();

    printf("==================================\n");
    printf("Total Tests Executed: %d\n", tests_run);
    printf("Passed: %d\n", tests_run - tests_failed);
    printf("Failed: %d\n", tests_failed);
    printf("==================================\n");

    if (tests_failed > 0) {
        printf("GLOBAL RESULT: FAILURE\n");
        return 1; 
    }

    printf("GLOBAL RESULT: SUCCESS\n");
    return 0;
}