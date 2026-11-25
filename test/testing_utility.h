#ifndef TESTING_UTILITY_H
#define TESTING_UTILITY_H

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

typedef struct test_t_ {
    int (*test_function)(void);
    char* test_name;
    bool is_enabled;
} test_t;

#define MAX_TESTS_PER_FILE 50

#define INIT_TEST_FILE() \
    static test_t tests[MAX_TESTS_PER_FILE]; \
    static unsigned int test_count = 0; 

#define TEST(name) \
    static int name(void)

#define REGISTER(name) \
    tests[test_count++] = (test_t){ \
        .test_function = &name, \
        .test_name = #name, \
        .is_enabled = true \
    };

#define SKIP_REGISTER(name) \
    tests[test_count++] = (test_t){ \
        .test_function = &name, \
        .test_name = #name, \
        .is_enabled = false \
    };

#define ANSI_COLOR_GREEN    "\033[32m"
#define ANSI_COLOR_YELLOW   "\033[33m"
#define ANSI_COLOR_RED      "\033[31m"
#define ANSI_COLOR_RESET    "\033[0m"

#define RUN_TESTS() \
    printf("\n====================\n"); \
    printf("Testing file \"%s\"\n", __FILE__); \
    printf("====================\n\n"); \
    unsigned int failed = 0; \
    unsigned int skipped = 0; \
    for (unsigned int i = 0; i < test_count; i++) { \
        if (!tests[i].is_enabled) { \
            printf(ANSI_COLOR_YELLOW"Skipping test \"%s\"\n"ANSI_COLOR_RESET, tests[i].test_name); \
            skipped++; \
            continue; \
        } \
        printf("Running test \"%s\"...\n", tests[i].test_name); \
        int result = tests[i].test_function(); \
        if (result != 0) { \
            printf(ANSI_COLOR_RED"Test failed!\n\n"ANSI_COLOR_RESET); \
            failed++; \
        } \
        else { \
            printf(ANSI_COLOR_GREEN"Test passed!\n\n"ANSI_COLOR_RESET); \
        } \
    } \
    if (failed > 0) { \
        printf("====================\n"); \
        printf(ANSI_COLOR_RED"File %s had %d failing test(s)!\n"ANSI_COLOR_RESET, __FILE__, failed); \
        printf("====================\n"); \
        return 1; \
    } \
    printf("====================\n"); \
    printf("Summary: %u passed, %u skipped, %u failed (%u total)\n", test_count - failed - skipped, skipped, failed, test_count); \
    printf("====================\n"); \
    return 0;

//#define FAIL(message)

#define ASSERT_TRUE(expression, message) \
    do { \
        if (!(expression)) { \
            printf(ANSI_COLOR_RED "[FAIL] %s (Line %d): %s\n" ANSI_COLOR_RESET, __func__, __LINE__, message); \
            return 1; \
        } \
    } while (0); \

#define ASSERT_FALSE(expression, message) ASSERT_TRUE(!(expression), message)

#define FORMAT_STRING(value) \
    (_Generic((value), \
        int:            "%d", \
        unsigned int:   "%u", \
        long:           "%ld", \
        unsigned long:  "%lu", \
        double:         "%f", \
        float:         "%f", \
        char*:          "%s", \
        const char*:    "%s", \
        default:        "unknown: %p" \
    ))

#define ASSERT_EQUAL(expected, actual, message) \
    do { \
        if (!(expected == actual)) { \
            printf(ANSI_COLOR_RED "[FAIL] %s (Line %d): %s\n" ANSI_COLOR_RESET, \
                __func__, __LINE__, message); \
            printf(ANSI_COLOR_RED "\texpected '"); \
            printf(FORMAT_STRING(expected), expected); \
            printf("' but got '"); \
            printf(FORMAT_STRING(actual), actual); \
            printf("'!\n" ANSI_COLOR_RESET); \
            return 1; \
        } \
    } while (0); 

#define ASSERT_STRING_EQUAL(expected, actual, message) \
    do { \
        if (strcmp(expected, actual) != 0) { \
            printf(ANSI_COLOR_RED "[FAIL] %s (Line %d): %s\n" ANSI_COLOR_RESET, \
                __func__, __LINE__, message); \
            printf(ANSI_COLOR_RED "\texpected '%s' but got '%s" ANSI_COLOR_RESET, expected, actual); \
            return 1; \
        } \
    } while (0); 

#define ASSERT_NOT_EQUAL(expected, actual, message) \
    do { \
        if (_Generic((expected), \
            char*: strcmp((expected), (actual)) == 0, \
            const char*: strcmp((expected), (actual)) == 0, \
            default: (expected == actual) \
        )) { \
            printf(ANSI_COLOR_RED "[FAIL] %s (Line %d): %s\n" ANSI_COLOR_RESET, \
                __func__, __LINE__, message); \
            printf(ANSI_COLOR_RED "\texpected '"); \
            printf(FORMAT_STRING(expected), expected); \
            printf("' to be different from '"); \
            printf(FORMAT_STRING(actual), actual); \
            printf("'!\n" ANSI_COLOR_RESET); \
            return 1; \
        } \
    } while (0); 

#define ASSERT_STRING_NOT_EQUAL(expected, actual, message) \
    do { \
        if (strcmp(expected, actual) == 0) { \
            printf(ANSI_COLOR_RED "[FAIL] %s (Line %d): %s\n" ANSI_COLOR_RESET, \
                __func__, __LINE__, message); \
            printf(ANSI_COLOR_RED "\texpected '%s' to be different from '%s" ANSI_COLOR_RESET, expected, actual); \
            return 1; \
        } \
    } while (0); 

#define FAIL(message) \
    do { \
        printf(ANSI_COLOR_RED "[FAIL] %s (Line %d): %s\n" ANSI_COLOR_RESET, \
        __func__, __LINE__, message); \
        return 1; \
    } while (0); 

#define ASSERT_NULL(value, message) ASSERT_EQUAL(NULL, value, message)
#define ASSERT_NOT_NULL(value, message) ASSERT_NOT_EQUAL(NULL, value, message)

#endif //TESTING_UTILITY_H