#include "../inc/hset/hset.h"
#include "../inc/vec/vec.h"
#include "../inc/hset/hset_integration.h"
#include "../inc/hset/hset_iter.h"
#include "tests.h"
#include <stddef.h>

void hset_iter_init_test(void) {
    hset_t hset;
    hset_iter_t iter;
    hset_init(&hset, 0, sizeof(size_t), NULL);

    ASSERT_TRUE("creating an iterator should fail if vec is null", hset_iter_init(NULL, &iter) == HSET_ERROR_NULL);
    ASSERT_TRUE("creating an iterator should fail if iter is null", hset_iter_init(&hset, NULL) == HSET_ERROR_NULL);
    ASSERT_TRUE("creating an iterator should fail for empty vec", hset_iter_init(&hset, &iter) == HSET_ERROR_INVALID);

    int vals[] = {1, 2, 3};
    hset_add(&hset, &vals[0]);
    hset_add(&hset, &vals[1]);
    hset_add(&hset, &vals[2]);

    ASSERT_TRUE("creating an iterator succeed for non-empty hset", hset_iter_init(&hset, &iter) == HSET_OK);

    hset_destroy(&hset);
}

void hset_iter_move_test() {
    hset_t hset;
    hset_iter_t iter;
   hset_init(&hset, 0, sizeof(int), NULL);

    int vals[] = {1, 2, 3};
    hset_add(&hset, &vals[0]);
    hset_add(&hset, &vals[1]);
    hset_add(&hset, &vals[2]);

    hset_iter_init(&hset, &iter);

    ASSERT_TRUE("moving forward should succeed", hset_iter_next(&iter) == HSET_ITER_OK);
    int temp = 0;
    hset_iter_get(&iter, &temp);
    ASSERT_TRUE("value should be written to temp", temp == 2);

    ASSERT_TRUE("should have next", hset_iter_has_next(&iter));
    ASSERT_TRUE("should be at index 1", iter.current_index == 1);

    hset_iter_next(&iter);
    ASSERT_TRUE("should not have next", !hset_iter_has_next(&iter));

    hset_destroy(&hset);
}

void hset_iter_invalidation() {
    const int N = 5;
    hset_t hsets[N];
    hset_iter_t iters[N];

    for (int i = 0; i < N; i++) {
        hset_init(&hsets[i], 0, sizeof(int), NULL);

        int vals[] = {1, 2, 3};
        hset_add(&hsets[i], &vals[0]);
        hset_add(&hsets[i], &vals[1]);
        hset_add(&hsets[i], &vals[2]);

        hset_iter_init(&hsets[i], &iters[i]);
    }

    // all these functiuons should invalidate the corresponding iterator
    int temp = 0;
    hset_add(&hsets[0], &temp);
    temp = 1;
    hset_remove(&hsets[1], &temp);
    hset_clear(&hsets[2]);

    vec_t vec;
    vec_init(&vec, 0, sizeof(int));
    temp = 1;
    vec_push_back(&vec, &temp);

    hset_add_all(&hsets[3], &vec);
    hset_remove_all(&hsets[4], &vec);


    for (int i = 1; i < N; i++) {
        ASSERT_TRUE("iter should be invalidated", hset_iter_next(&iters[i]) == HSET_ITER_INVALID);
        hset_destroy(&hsets[i]);
    }
}

void hset_iter_remove_insert() {
    hset_t hset;
    hset_iter_t iter;
    hset_init(&hset, 0, sizeof(int), NULL);

    int vals[] = {1, 2, 3};
    hset_add(&hset, &vals[0]);
    hset_add(&hset, &vals[1]);
    hset_add(&hset, &vals[2]);

    hset_iter_init(&hset, &iter);

    int temp = 0;
    ASSERT_TRUE("removing element should succeed", hset_iter_remove(&iter) == HSET_ITER_OK);
    ASSERT_TRUE("removing without moving should fail", hset_iter_remove(&iter) == HSET_ITER_INVALID);
    ASSERT_TRUE("get after remove without moving should fail", hset_iter_get(&iter, &temp) == HSET_ITER_INVALID);

    hset_iter_next(&iter);
    temp = 10;
    ASSERT_TRUE("get should unblock after move", hset_iter_get(&iter, &temp) == HSET_ITER_OK);
    ASSERT_TRUE("remove should unblock after move", hset_iter_remove(&iter) == HSET_ITER_OK);
}

void hset_iter_tests() {
    printf("--- RUNNING HASH SET ITERATOR TESTS ---\n");

    RUN_TEST(hset_iter_init_test);
    RUN_TEST(hset_iter_move_test);
    RUN_TEST(hset_iter_invalidation);
    RUN_TEST(hset_iter_remove_insert);

    printf("\n");
}
