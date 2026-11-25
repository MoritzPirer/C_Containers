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

TEST(test_givenValidIterator_whenSet_thenSucceeds) {
    vec_t vec;
    vec_iter_t iter;
    int temp = 10;
    init_test_vec(&vec);
    vec_iter_init(&vec, &iter, 0);

    ASSERT_EQUAL(VEC_ITER_OK, vec_iter_set(&iter, &temp),
        "setting should succeed");

    vec_destroy(&vec);
    return 0;
}

TEST(test_givenValidIterator_whenSet_thenUpdatesVectorValue) {
    vec_t vec;
    vec_iter_t iter;
    int temp = 10;
    init_test_vec(&vec);
    vec_iter_init(&vec, &iter, 0);

    vec_iter_set(&iter, &temp);
    temp = 0;
    vec_get(&vec, 0, &temp);

    ASSERT_EQUAL(10, temp,
        "setting through iterator should update the vector");

    vec_destroy(&vec);
    return 0;
}

TEST(test_givenValidIterator_whenVectorValueChanges_thenGetReturnsNewValue) {
    vec_t vec;
    vec_iter_t iter;
    int temp = 15;
    init_test_vec(&vec);
    vec_iter_init(&vec, &iter, 0);

    vec_set(&vec, 0, &temp);
    temp = 0;
    vec_iter_get(&iter, &temp);

    ASSERT_EQUAL(15, temp,
        "iterator should read the updated vector value");

    vec_destroy(&vec);
    return 0;
}

int main(void) {
    REGISTER(test_givenValidIterator_whenSet_thenSucceeds)
    REGISTER(test_givenValidIterator_whenSet_thenUpdatesVectorValue)
    REGISTER(test_givenValidIterator_whenVectorValueChanges_thenGetReturnsNewValue)

    RUN_TESTS()
}
