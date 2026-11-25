#include "test/testing_utility.h"
#include "inc/vec/vec.h"

INIT_TEST_FILE()

TEST(test_givenEmptyVec_thenSizeIsZero) {
    vec_t vec;
    vec_init(&vec, 0, sizeof(size_t));
    ASSERT_EQUAL(0, vec_size(&vec), "Empty vector must have size zero")

    return 0;
}

TEST(test_givenEmptyVec_whenElementIsPushed_thenSizeIsOne) {
    vec_t vec;
    vec_init(&vec, 0, sizeof(size_t));

    size_t element = 1;
    vec_push_back(&vec, &element);

    ASSERT_EQUAL(1UL, vec_size(&vec), "Size must equal 1 after element is pushed")

    return 0;
}

TEST(test_givenVec_whenLastElementIsPopped_thenSizeIsZero) {
    vec_t vec;
    vec_init(&vec, 0, sizeof(size_t));

    size_t element = 1;
    vec_push_back(&vec, &element);
    vec_pop_back(&vec, &element);

    ASSERT_EQUAL(0, vec_size(&vec), "Size must equal 0 arter last element is popped")

    return 0;
}

TEST(test_givenVec_whenCleared_thenSizeIsZero) {
    vec_t vec;
    vec_init(&vec, 0, sizeof(size_t));

    size_t element = 1;
    vec_push_back(&vec, &element);
    vec_push_back(&vec, &element);
    vec_push_back(&vec, &element);
    ASSERT_EQUAL(3, vec_size(&vec), "Size must equal 3 after 3 pushes");

    vec_clear(&vec);
    ASSERT_EQUAL(0, vec_size(&vec), "Size must equal 0 arter all elements are popped")

    return 0;
}

TEST(test_givenVec_whenPartsAreErased_thenSizeMatches) {
    vec_t vec;
    vec_init(&vec, 0, sizeof(size_t));

    size_t element = 1;
    vec_push_back(&vec, &element);
    vec_push_back(&vec, &element);
    vec_push_back(&vec, &element);
    vec_push_back(&vec, &element);
    vec_push_back(&vec, &element);

    vec_erase_from(&vec, 1);
    ASSERT_EQUAL(1, vec_size(&vec), "Size must be 1 after erasing from index 1 forward")

    vec_push_back(&vec, &element);
    vec_push_back(&vec, &element);
    vec_push_back(&vec, &element);
    vec_push_back(&vec, &element);
    vec_push_back(&vec, &element);
    
    vec_erase_to(&vec, 3);
    ASSERT_EQUAL(2, vec_size(&vec), "Size must be 2 after erasing up toindex 2")

    return 0;
}

TEST(test_givenVec_whenResized_thenSizeIncreases) {
    vec_t vec;
    vec_init(&vec, 0, sizeof(int));

    vec_resize(&vec, 20);
    ASSERT_EQUAL(20, vec_size(&vec), "Resizing should increse size");

    return 0;
}

int main(void) {
    REGISTER(test_givenEmptyVec_thenSizeIsZero)
    REGISTER(test_givenEmptyVec_whenElementIsPushed_thenSizeIsOne)
    REGISTER(test_givenVec_whenLastElementIsPopped_thenSizeIsZero)
    REGISTER(test_givenVec_whenCleared_thenSizeIsZero)
    REGISTER(test_givenVec_whenPartsAreErased_thenSizeMatches)
    REGISTER(test_givenVec_whenResized_thenSizeIncreases)

    RUN_TESTS()
}
