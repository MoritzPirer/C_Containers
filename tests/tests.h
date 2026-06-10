#ifndef TEST_SUITE_H
#define TEST_SUITE_H

#include <stdio.h>

// Global counters for test tracking
extern int tests_run;
extern int tests_failed;

#define ANSI_COLOR_GREEN   "\033[32m"
#define ANSI_COLOR_RED     "\033[31m"
#define ANSI_COLOR_RESET   "\033[0m"
// The core assertion macro
#define ASSERT_TRUE(msg, expression) do { \
    tests_run++; \
    if (!(expression)) { \
        printf(ANSI_COLOR_RED "  [FAIL] %s (Line %d): %s\n" ANSI_COLOR_RESET, __func__, __LINE__, msg); \
        tests_failed++; \
        return; \
    } \
} while(0)

// Helper for checking integer equality
#define ASSERT_INT_EQ(msg, expected, actual) \
    ASSERT_TRUE(msg, (expected) == (actual))

#define ASSERT_INT_GREATER(msg, expected, actual) \
    ASSERT_TRUE(msg, (expected) > (actual))

#define ASSERT_INT_LESS(msg, expected, actual) \
    ASSERT_TRUE(msg, (expected) < (actual))

#define ASSERT_INT_NEQ(msg, expected, actual) \
    ASSERT_TRUE(msg, (expected) != (actual))

#define ASSERT_PTR_EQ(msg, expected, actual) \
    ASSERT_TRUE(msg, (void*)(expected) == (void*)(actual))

#define ASSERT_FALSE(msg, expression) \
    ASSERT_TRUE(msg, !(expression))

#define RUN_TEST(test_func) do { \
    int failed_before = tests_failed; \
    test_func(); \
    if (tests_failed == failed_before) { \
        printf(ANSI_COLOR_GREEN"  [PASS] %s%s\n", #test_func, ANSI_COLOR_RESET); \
    } \
} while(0)

// Print final summary
#define TEST_SUMMARY() do { \
    printf("\n--- Test Summary ---\n"); \
    printf("Total Tests Run: %d\n", tests_run); \
    printf("Passed: %d\n", tests_run - tests_failed); \
    printf("Failed: %d\n", tests_failed); \
    if (tests_failed > 0) { \
        printf("Result: FAILURE\n"); \
    } else { \
        printf("Result: SUCCESS\n"); \
    } \
} while(0)

#endif // TEST_SUITE_H