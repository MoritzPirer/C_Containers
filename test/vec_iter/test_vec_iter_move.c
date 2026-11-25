#include "test/testing_utility.h"
#include "inc/vec/vec_iter.h"

INIT_TEST_FILE()

static void init_test_vec(vec_t* vec) {
    vec_init(vec, 0, sizeof(int));

    int vals[] = {1, 2, 3};
    vec_push_back(vec, &vals[0]);
    vec_push_back(vec, &vals[1]);
    vec_push_back(vec, &vals[2]);
}

TEST(test_givenIteratorAtFirstElement_whenMovePrevious_thenReturnsEnd) {
    vec_t vec;
    vec_iter_t iter;
    init_test_vec(&vec);
    vec_iter_init(&vec, &iter, 0);

    ASSERT_EQUAL(VEC_ITER_END, vec_iter_previous(&iter),
        "moving back should fail at index 0");

    vec_destroy(&vec);
    return 0;
}

TEST(test_givenIteratorAtFirstElement_thenHasNoPrevious) {
    vec_t vec;
    vec_iter_t iter;
    init_test_vec(&vec);
    vec_iter_init(&vec, &iter, 0);

    ASSERT_EQUAL(false, vec_iter_has_previous(&iter),
        "should not have previous at index 0");

    vec_destroy(&vec);
    return 0;
}

TEST(test_givenIteratorAtFirstElement_whenMoveNext_thenSucceeds) {
    vec_t vec;
    vec_iter_t iter;
    init_test_vec(&vec);
    vec_iter_init(&vec, &iter, 0);

    ASSERT_EQUAL(VEC_ITER_OK, vec_iter_next(&iter),
        "moving forward should succeed");

    vec_destroy(&vec);
    return 0;
}

TEST(test_givenIteratorAtFirstElement_whenMoveNext_thenPointsToSecondElement) {
    vec_t vec;
    vec_iter_t iter;
    int temp = 0;
    init_test_vec(&vec);
    vec_iter_init(&vec, &iter, 0);

    vec_iter_next(&iter);
    vec_iter_get(&iter, &temp);

    ASSERT_EQUAL(2, temp,
        "iterator should point to the second element");

    vec_destroy(&vec);
    return 0;
}

TEST(test_givenIteratorAtSecondElement_thenHasNext) {
    vec_t vec;
    vec_iter_t iter;
    init_test_vec(&vec);
    vec_iter_init(&vec, &iter, 0);

    vec_iter_next(&iter);

    ASSERT_EQUAL(true, vec_iter_has_next(&iter),
        "iterator should have next");

    vec_destroy(&vec);
    return 0;
}

TEST(test_givenIteratorAtSecondElement_thenHasPrevious) {
    vec_t vec;
    vec_iter_t iter;
    init_test_vec(&vec);
    vec_iter_init(&vec, &iter, 0);

    vec_iter_next(&iter);

    ASSERT_EQUAL(true, vec_iter_has_previous(&iter),
        "iterator should have previous");

    vec_destroy(&vec);
    return 0;
}

TEST(test_givenIteratorAtSecondElement_thenCurrentIndexIsOne) {
    vec_t vec;
    vec_iter_t iter;
    init_test_vec(&vec);
    vec_iter_init(&vec, &iter, 0);

    vec_iter_next(&iter);

    ASSERT_EQUAL(1, iter.current_index,
        "iterator should be at index 1");

    vec_destroy(&vec);
    return 0;
}

TEST(test_givenIteratorAtLastElement_thenHasNoNext) {
    vec_t vec;
    vec_iter_t iter;
    init_test_vec(&vec);
    vec_iter_init(&vec, &iter, 0);

    vec_iter_next(&iter);
    vec_iter_next(&iter);

    ASSERT_EQUAL(false, vec_iter_has_next(&iter),
        "iterator should not have next");

    vec_destroy(&vec);
    return 0;
}

int main(void) {
    REGISTER(test_givenIteratorAtFirstElement_whenMovePrevious_thenReturnsEnd)
    REGISTER(test_givenIteratorAtFirstElement_thenHasNoPrevious)
    REGISTER(test_givenIteratorAtFirstElement_whenMoveNext_thenSucceeds)
    REGISTER(test_givenIteratorAtFirstElement_whenMoveNext_thenPointsToSecondElement)
    REGISTER(test_givenIteratorAtSecondElement_thenHasNext)
    REGISTER(test_givenIteratorAtSecondElement_thenHasPrevious)
    REGISTER(test_givenIteratorAtSecondElement_thenCurrentIndexIsOne)
    REGISTER(test_givenIteratorAtLastElement_thenHasNoNext)

    RUN_TESTS()
}
