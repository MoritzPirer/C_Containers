#include "test/testing_utility.h"
#include "inc/vec/vec.h"

INIT_TEST_FILE()

TEST(test_givenElementSizeZero_thenInitFails) {
    vec_t vec;
    vec_status_t result = vec_init(&vec, 1, 0);
    ASSERT_EQUAL(VEC_ERROR_INVALID, result, "Intitialization with size 0 shoud fail");

    return 0;
}

TEST(test_givenNullVec_thenInitFails) {
    vec_status_t result = vec_init(NULL, 1, 1);
    ASSERT_EQUAL(VEC_ERROR_NULL, result, "Initialization with null vec_t should fail")

    return 0;
}

TEST(test_givenInitialSizeZero_thenInitSucceeds) {
    vec_t vec;
    vec_status_t result = vec_init(&vec, 0, sizeof(int));

    ASSERT_EQUAL(VEC_OK, result, "Initialization should succeed")
    ASSERT_EQUAL(sizeof(int), vec.item_size, "Item size should match given element size")
    ASSERT_EQUAL(VEC_MIN_CAPACITY, vec.capacity, "Capacity allocated should match baseline VEC_MIN_CAPACITY")
    ASSERT_EQUAL(0, vec.size, "Size used should be exactly 0")

    return 0;
}

TEST(test_givenLargeCapacity_thenInitSucceeds) {
    vec_t vec;
    size_t capacity = 1000000;
    vec_status_t result = vec_init(&vec, capacity, sizeof(int));

    ASSERT_EQUAL(VEC_OK, result, "Initialization should succeed")
    ASSERT_EQUAL(sizeof(int), vec.item_size, "Item size should match given element size")
    ASSERT_EQUAL(capacity, vec.capacity, "Capacity allocated should match requested capacity")
    ASSERT_EQUAL(0, vec.size, "Size used should be exactly 0")

    return 0;
}

int main(void) {
    REGISTER(test_givenElementSizeZero_thenInitFails)
    REGISTER(test_givenNullVec_thenInitFails)
    REGISTER(test_givenInitialSizeZero_thenInitSucceeds)
    REGISTER(test_givenLargeCapacity_thenInitSucceeds)

    RUN_TESTS()
}
