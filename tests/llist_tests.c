#include "inc/llist/llist.h"
#include "tests.h"

void test_llist_push_back(void) {
    llist_t llist;
    llist_init(&llist, sizeof(int));

    int i = 1;
    llist_push_back(&llist, &i);

    int read = 0;
    llist_status_t result = llist_get(&llist, 0, &read);
    ASSERT_TRUE("reading non-empty llist", result == LLIST_OK);
    ASSERT_TRUE("get value that was pushed", read == i);

    i = 2;
    llist_push_back(&llist, &i);
    result = llist_get(&llist, 1, &read);

    ASSERT_TRUE("reading non-empty llist", result == LLIST_OK);
    ASSERT_TRUE("get value that was pushed", read == i);

    llist_destroy(&llist);
}

void test_llist_push_front(void) {
    llist_t llist;
    llist_init(&llist, sizeof(int));

    int i = 1;
    llist_push_front(&llist, &i);

    int read = 0;
    llist_status_t result = llist_get(&llist, 0, &read);
    ASSERT_TRUE("reading non-empty llist", result == LLIST_OK);
    ASSERT_TRUE("get value that was pushed", read == i);

    i = 2;
    llist_push_front(&llist, &i);
    result = llist_get(&llist, 0, &read);

    ASSERT_TRUE("reading non-empty llist", result == LLIST_OK);
    ASSERT_TRUE("get value that was pushed", read == i);

    llist_destroy(&llist);
}

void test_llist_pop_front(void) {
    llist_t llist;
    llist_init(&llist, sizeof(int));

    int i = 1;
    llist_push_front(&llist, &i);

    i = 2;
    llist_push_front(&llist, &i);

    int popped = 0;
    llist_status_t result = llist_pop_front(&llist, &popped);

    ASSERT_TRUE("popping from non-empty llist", result == LLIST_OK);
    ASSERT_TRUE("popped front value", popped == 2);
    ASSERT_TRUE("element no longer in list", llist_size(&llist) == 1);

    result = llist_pop_front(&llist, &popped);
    ASSERT_TRUE("popping from only element", result == LLIST_OK);
}

void test_llist_pop_back(void) {
    llist_t llist;
    llist_init(&llist, sizeof(int));

    int i = 1;
    llist_push_front(&llist, &i);

    i = 2;
    llist_push_front(&llist, &i);

    int popped = 0;
    llist_status_t result = llist_pop_back(&llist, &popped);

    ASSERT_TRUE("popping from non-empty llist", result == LLIST_OK);
    ASSERT_TRUE("popped front value", popped == 1);
    ASSERT_TRUE("element no longer in list", llist_size(&llist) == 1);

    result = llist_pop_back(&llist, &popped);
    ASSERT_TRUE("popping from only element", result == LLIST_OK);
}

void test_llist_get(void) {
    llist_t llist;
    llist_init(&llist, sizeof(int));
    
    for (int i = 0; i < 10; i++) {
        llist_push_back(&llist, &i);
    }

    int read = 0;
    llist_status_t result = llist_get(&llist, 1, &read);

    ASSERT_TRUE("get at valid index", result == LLIST_OK);
    ASSERT_TRUE("read correct value", read == 1);

    result = llist_get(&llist, 100, &read);

    ASSERT_TRUE("out-of-bounds read fails", result == LLIST_ERROR_BOUNDS);
}

void test_llist_set(void) {
    llist_t llist;
    llist_init(&llist, sizeof(int));
    
    for (int i = 0; i < 10; i++) {
        llist_push_back(&llist, &i);
    }

    int value = 50;
    llist_status_t result = llist_set(&llist, 1, &value);

    ASSERT_TRUE("set at valid index", result == LLIST_OK);

    int read;
    llist_get(&llist, 1, &read);
    ASSERT_TRUE("read reflects write", value == read);

    result = llist_set(&llist, 100, &value);

    ASSERT_TRUE("out-of-bounds write fails", result == LLIST_ERROR_BOUNDS);

}

void llist_tests(void) {
    printf("--- RUNNING CORE LLIST TESTS ---\n");

    RUN_TEST(test_llist_push_back);
    RUN_TEST(test_llist_push_front);
    RUN_TEST(test_llist_pop_front);
    RUN_TEST(test_llist_pop_back);
    RUN_TEST(test_llist_set);
    RUN_TEST(test_llist_get);

    printf("\n");
}
