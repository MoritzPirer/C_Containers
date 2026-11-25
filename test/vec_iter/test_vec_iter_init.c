#include "test/testing_utility.h"
#include "inc/vec/vec_iter.h"

INIT_TEST_FILE()

TEST(test_givenNullVec_thenInitFails) {
    vec_iter_t iter;
    ASSERT_EQUAL(VEC_ERROR_NULL, vec_iter_init(NULL, &iter, 0), "creating an iterator should fail if vec is null")

    return 0;
}

TEST(test_givenNullIterator_thenInitFails) {
    vec_t vec;
    vec_init(&vec, 0, sizeof(int));

    ASSERT_EQUAL(VEC_ERROR_NULL, vec_iter_init(&vec, NULL, 0), "creating an iterator should fail if iterator is null")

    return 0;
}

TEST(test_givenEmptyIterator_thenInitFails) {
    vec_t vec;
    vec_init(&vec, 0, sizeof(int));
    vec_iter_t iter;

    ASSERT_EQUAL(VEC_ERROR_BOUNDS, vec_iter_init(&vec, &iter, 0), "creating an iterator should fail if iterator is null")

    return 0;

}

TEST(test_givenNonEmptyIterator_thenInitSucceeds) {
    vec_t vec;
    vec_init(&vec, 0, sizeof(int));

    int vals[] = {1, 2, 3};
    vec_push_back(&vec, &vals[0]);
    vec_push_back(&vec, &vals[1]);
    vec_push_back(&vec, &vals[2]);

    vec_iter_t iter;

    ASSERT_EQUAL(VEC_OK, vec_iter_init(&vec, &iter, 0), "creating an iterator succeed for non-empty vec")

    vec_destroy(&vec);

    return 0;
}

TEST(test_givenNonEmptyIterator_whenInitialIndexIsOutOfBounds_thenInitFails) {
    vec_t vec;
    vec_init(&vec, 0, sizeof(int));

    int vals[] = {1, 2, 3};
    vec_push_back(&vec, &vals[0]);
    vec_push_back(&vec, &vals[1]);
    vec_push_back(&vec, &vals[2]);

    vec_iter_t iter;

    ASSERT_EQUAL(VEC_ERROR_BOUNDS, vec_iter_init(&vec, &iter, 3), "creating an iterator succeed for non-empty vec")

    return 0;

}

int main(void) {
    REGISTER(test_givenNullVec_thenInitFails)
    REGISTER(test_givenNullIterator_thenInitFails)
    REGISTER(test_givenEmptyIterator_thenInitFails)
    REGISTER(test_givenNonEmptyIterator_thenInitSucceeds)
    REGISTER(test_givenNonEmptyIterator_whenInitialIndexIsOutOfBounds_thenInitFails)

    RUN_TESTS()
}
