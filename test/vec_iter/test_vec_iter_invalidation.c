#include "test/testing_utility.h"
#include "inc/vec/vec_iter.h"
#include "inc/vec/vec_algs.h"


INIT_TEST_FILE()

static void init_test_vec(vec_t* vec) {
    vec_init(vec, 0, sizeof(int));

    int vals[] = {1, 2, 3};
    vec_push_back(vec, &vals[0]);
    vec_push_back(vec, &vals[1]);
    vec_push_back(vec, &vals[2]);
}

TEST(test_givenIterator_whenEraseFromTo_thenIteratorIsInvalidated) {
    vec_t vec;
    vec_iter_t iter;
    init_test_vec(&vec);
    vec_iter_init(&vec, &iter, 0);

    vec_erase_from_to(&vec, 0, 1);

    ASSERT_EQUAL(VEC_ITER_INVALID, vec_iter_next(&iter),
        "iterator should be invalidated after erase_from_to");

    vec_destroy(&vec);
    return 0;
}

TEST(test_givenIterator_whenEraseFrom_thenIteratorIsInvalidated) {
    vec_t vec;
    vec_iter_t iter;
    init_test_vec(&vec);
    vec_iter_init(&vec, &iter, 0);

    vec_erase_from(&vec, 1);

    ASSERT_EQUAL(VEC_ITER_INVALID, vec_iter_next(&iter),
        "iterator should be invalidated after erase_from");

    vec_destroy(&vec);
    return 0;
}

TEST(test_givenIterator_whenEraseTo_thenIteratorIsInvalidated) {
    vec_t vec;
    vec_iter_t iter;
    init_test_vec(&vec);
    vec_iter_init(&vec, &iter, 0);

    vec_erase_to(&vec, 1);

    ASSERT_EQUAL(VEC_ITER_INVALID, vec_iter_next(&iter),
        "iterator should be invalidated after erase_to");

    vec_destroy(&vec);
    return 0;
}

TEST(test_givenIterator_whenEraseAt_thenIteratorIsInvalidated) {
    vec_t vec;
    vec_iter_t iter;
    init_test_vec(&vec);
    vec_iter_init(&vec, &iter, 0);

    vec_erase_at(&vec, 1);

    ASSERT_EQUAL(VEC_ITER_INVALID, vec_iter_next(&iter),
        "iterator should be invalidated after erase_at");

    vec_destroy(&vec);
    return 0;
}

TEST(test_givenIterator_whenClear_thenIteratorIsInvalidated) {
    vec_t vec;
    vec_iter_t iter;
    init_test_vec(&vec);
    vec_iter_init(&vec, &iter, 0);

    vec_clear(&vec);

    ASSERT_EQUAL(VEC_ITER_INVALID, vec_iter_next(&iter),
        "iterator should be invalidated after clear");

    vec_destroy(&vec);
    return 0;
}

TEST(test_givenIterator_whenSwap_thenIteratorIsInvalidated) {
    vec_t vec_a, vec_b;
    vec_iter_t iter;
    init_test_vec(&vec_a);
    init_test_vec(&vec_b);
    vec_iter_init(&vec_a, &iter, 0);

    vec_swap(&vec_a, &vec_b);

    ASSERT_EQUAL(VEC_ITER_INVALID, vec_iter_next(&iter),
        "iterator should be invalidated after swap");

    vec_destroy(&vec_a);
    vec_destroy(&vec_b);
    return 0;
}

TEST(test_givenIteratorOnSecondVec_whenSwap_thenIteratorIsInvalidated) {
    vec_t vec_a, vec_b;
    vec_iter_t iter;
    init_test_vec(&vec_a);
    init_test_vec(&vec_b);
    vec_iter_init(&vec_b, &iter, 0);

    vec_swap(&vec_a, &vec_b);

    ASSERT_EQUAL(VEC_ITER_INVALID, vec_iter_next(&iter),
        "iterator should be invalidated after swap");

    vec_destroy(&vec_a);
    vec_destroy(&vec_b);
    return 0;
}

TEST(test_givenIterator_whenAddAll_thenIteratorIsInvalidated) {
    vec_t vec_a, vec_b;
    vec_iter_t iter;
    init_test_vec(&vec_a);
    init_test_vec(&vec_b);
    vec_iter_init(&vec_a, &iter, 0);

    vec_add_all(&vec_a, &vec_b);

    ASSERT_EQUAL(VEC_ITER_INVALID, vec_iter_next(&iter),
        "iterator should be invalidated after add_all");

    vec_destroy(&vec_a);
    vec_destroy(&vec_b);
    return 0;
}

TEST(test_givenIterator_whenReverse_thenIteratorIsInvalidated) {
    vec_t vec;
    vec_iter_t iter;
    init_test_vec(&vec);
    vec_iter_init(&vec, &iter, 0);

    vec_reverse(&vec);

    ASSERT_EQUAL(VEC_ITER_INVALID, vec_iter_next(&iter),
        "iterator should be invalidated after reverse");

    vec_destroy(&vec);
    return 0;
}

TEST(test_givenIterator_whenPushBack_thenIteratorIsInvalidated) {
    vec_t vec;
    vec_iter_t iter;
    int temp = 0;
    init_test_vec(&vec);
    vec_iter_init(&vec, &iter, 0);

    vec_push_back(&vec, &temp);

    ASSERT_EQUAL(VEC_ITER_INVALID, vec_iter_next(&iter),
        "iterator should be invalidated after push_back");

    vec_destroy(&vec);
    return 0;
}

TEST(test_givenIterator_whenPushFront_thenIteratorIsInvalidated) {
    vec_t vec;
    vec_iter_t iter;
    int temp = 0;
    init_test_vec(&vec);
    vec_iter_init(&vec, &iter, 0);

    vec_push_front(&vec, &temp);

    ASSERT_EQUAL(VEC_ITER_INVALID, vec_iter_next(&iter),
        "iterator should be invalidated after push_front");

    vec_destroy(&vec);
    return 0;
}

TEST(test_givenIterator_whenPopBack_thenIteratorIsInvalidated) {
    vec_t vec;
    vec_iter_t iter;
    int temp = 0;
    init_test_vec(&vec);
    vec_iter_init(&vec, &iter, 0);

    vec_pop_back(&vec, &temp);

    ASSERT_EQUAL(VEC_ITER_INVALID, vec_iter_next(&iter),
        "iterator should be invalidated after pop_back");

    vec_destroy(&vec);
    return 0;
}

TEST(test_givenIterator_whenPopFront_thenIteratorIsInvalidated) {
    vec_t vec;
    vec_iter_t iter;
    int temp = 0;
    init_test_vec(&vec);
    vec_iter_init(&vec, &iter, 0);

    vec_pop_front(&vec, &temp);

    ASSERT_EQUAL(VEC_ITER_INVALID, vec_iter_next(&iter),
        "iterator should be invalidated after pop_front");

    vec_destroy(&vec);
    return 0;
}

TEST(test_givenIterator_whenInsert_thenIteratorIsInvalidated) {
    vec_t vec;
    vec_iter_t iter;
    int temp = 0;
    init_test_vec(&vec);
    vec_iter_init(&vec, &iter, 0);

    vec_insert(&vec, 0, &temp);

    ASSERT_EQUAL(VEC_ITER_INVALID, vec_iter_next(&iter),
        "iterator should be invalidated after insert");

    vec_destroy(&vec);
    return 0;
}

TEST(test_givenIterator_whenSort_thenIteratorIsInvalidated) {
    vec_t vec;
    vec_iter_t iter;
    init_test_vec(&vec);
    vec_iter_init(&vec, &iter, 0);

    vec_sort(&vec, vec_default_ordering);

    ASSERT_EQUAL(VEC_ITER_INVALID, vec_iter_next(&iter),
        "iterator should be invalidated after sort");

    vec_destroy(&vec);
    return 0;
}

/* ==================== REMOVE AND INSERT ==================== */

TEST(test_givenValidIterator_whenRemove_thenSucceeds) {
    vec_t vec;
    vec_iter_t iter;
    init_test_vec(&vec);
    vec_iter_init(&vec, &iter, 0);

    ASSERT_EQUAL(VEC_ITER_OK, vec_iter_remove(&iter),
        "removing an element should succeed");

    vec_destroy(&vec);
    return 0;
}

TEST(test_givenIteratorAfterRemove_thenRemoveFails) {
    vec_t vec;
    vec_iter_t iter;
    init_test_vec(&vec);
    vec_iter_init(&vec, &iter, 0);

    vec_iter_remove(&iter);

    ASSERT_EQUAL(VEC_ITER_INVALID, vec_iter_remove(&iter),
        "removing again without moving should fail");

    vec_destroy(&vec);
    return 0;
}

TEST(test_givenIteratorAfterRemove_thenGetFails) {
    vec_t vec;
    vec_iter_t iter;
    int temp = 0;
    init_test_vec(&vec);
    vec_iter_init(&vec, &iter, 0);

    vec_iter_remove(&iter);

    ASSERT_EQUAL(VEC_ITER_INVALID, vec_iter_get(&iter, &temp),
        "get after remove without moving should fail");

    vec_destroy(&vec);
    return 0;
}

TEST(test_givenIteratorAfterRemove_thenSetFails) {
    vec_t vec;
    vec_iter_t iter;
    int temp = 0;
    init_test_vec(&vec);
    vec_iter_init(&vec, &iter, 0);

    vec_iter_remove(&iter);

    ASSERT_EQUAL(VEC_ITER_INVALID, vec_iter_set(&iter, &temp),
        "set after remove without moving should fail");

    vec_destroy(&vec);
    return 0;
}

TEST(test_givenIteratorAfterRemove_whenInsert_thenSucceeds) {
    vec_t vec;
    vec_iter_t iter;
    int temp = 0;
    init_test_vec(&vec);
    vec_iter_init(&vec, &iter, 0);

    vec_iter_remove(&iter);

    ASSERT_EQUAL(VEC_ITER_OK, vec_iter_insert(&iter, &temp),
        "insert should work even after remove");

    vec_destroy(&vec);
    return 0;
}

TEST(test_givenIteratorAfterRemove_whenMoveNext_thenSetSucceeds) {
    vec_t vec;
    vec_iter_t iter;
    int temp = 10;
    init_test_vec(&vec);
    vec_iter_init(&vec, &iter, 0);

    vec_iter_remove(&iter);
    vec_iter_next(&iter);

    ASSERT_EQUAL(VEC_ITER_OK, vec_iter_set(&iter, &temp),
        "set should work again after moving");

    vec_destroy(&vec);
    return 0;
}

TEST(test_givenIteratorAfterRemove_whenMoveNext_thenGetSucceeds) {
    vec_t vec;
    vec_iter_t iter;
    int temp = 0;
    init_test_vec(&vec);
    vec_iter_init(&vec, &iter, 0);

    vec_iter_remove(&iter);
    vec_iter_next(&iter);

    ASSERT_EQUAL(VEC_ITER_OK, vec_iter_get(&iter, &temp),
        "get should work again after moving");

    vec_destroy(&vec);
    return 0;
}

TEST(test_givenIteratorAfterRemove_whenMoveNext_thenRemoveSucceeds) {
    vec_t vec;
    vec_iter_t iter;
    init_test_vec(&vec);
    vec_iter_init(&vec, &iter, 0);

    vec_iter_remove(&iter);
    vec_iter_next(&iter);

    ASSERT_EQUAL(VEC_ITER_OK, vec_iter_remove(&iter),
        "remove should work again after moving");

    vec_destroy(&vec);
    return 0;
}

int main(void) {
    REGISTER(test_givenIterator_whenEraseFromTo_thenIteratorIsInvalidated)
    REGISTER(test_givenIterator_whenEraseFrom_thenIteratorIsInvalidated)
    REGISTER(test_givenIterator_whenEraseTo_thenIteratorIsInvalidated)
    REGISTER(test_givenIterator_whenEraseAt_thenIteratorIsInvalidated)
    REGISTER(test_givenIterator_whenClear_thenIteratorIsInvalidated)
    REGISTER(test_givenIterator_whenSwap_thenIteratorIsInvalidated)
    REGISTER(test_givenIteratorOnSecondVec_whenSwap_thenIteratorIsInvalidated)
    REGISTER(test_givenIterator_whenAddAll_thenIteratorIsInvalidated)
    REGISTER(test_givenIterator_whenReverse_thenIteratorIsInvalidated)
    REGISTER(test_givenIterator_whenPushBack_thenIteratorIsInvalidated)
    REGISTER(test_givenIterator_whenPushFront_thenIteratorIsInvalidated)
    REGISTER(test_givenIterator_whenPopBack_thenIteratorIsInvalidated)
    REGISTER(test_givenIterator_whenPopFront_thenIteratorIsInvalidated)
    REGISTER(test_givenIterator_whenInsert_thenIteratorIsInvalidated)
    REGISTER(test_givenIterator_whenSort_thenIteratorIsInvalidated)

    REGISTER(test_givenValidIterator_whenRemove_thenSucceeds)
    REGISTER(test_givenIteratorAfterRemove_thenRemoveFails)
    REGISTER(test_givenIteratorAfterRemove_thenGetFails)
    REGISTER(test_givenIteratorAfterRemove_thenSetFails)
    REGISTER(test_givenIteratorAfterRemove_whenInsert_thenSucceeds)
    REGISTER(test_givenIteratorAfterRemove_whenMoveNext_thenSetSucceeds)
    REGISTER(test_givenIteratorAfterRemove_whenMoveNext_thenGetSucceeds)
    REGISTER(test_givenIteratorAfterRemove_whenMoveNext_thenRemoveSucceeds)

    RUN_TESTS()
}
