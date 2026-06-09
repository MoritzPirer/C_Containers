#include "../inc/hset/hset.h"
#include "tests.h"

void hset_basic() {
    hset_t hset;
    hset_init(&hset, 8, sizeof(int), NULL);

    int item = 15;
    hset_add(&hset, &item);

    ASSERT_TRUE("hset doesn't contain item after add", hset_contains(&hset, &item));

    item = 10;
    hset_add(&hset, &item);

    ASSERT_TRUE("hset doesn't contain item after add", hset_contains(&hset, &item));
    
    hset_remove(&hset, &item);

    ASSERT_FALSE("hset contains item after remove", hset_contains(&hset, &item));

    hset_destroy(&hset);
}

void hset_grow() {
    hset_t hset;
    hset_init(&hset, 4, sizeof(int), NULL);

    for (int i = 1; i < 11; i++) {
        hset_add(&hset, &i);
    }

    ASSERT_TRUE("capacity should be at least 8 here", hset.capacity >= 8);

    for (int i = 1; i < 11; i++) {
        ASSERT_TRUE("value not contained when it should be", hset_contains(&hset, &i));
    }

    hset_destroy(&hset);
}

void hset_tests() {
    printf("--- RUNNING CORE HSET TESTS ---\n");

    RUN_TEST(hset_basic);
    RUN_TEST(hset_grow);

    printf("\n");
}