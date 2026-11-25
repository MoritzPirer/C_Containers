#include "testing_utility.h"

INIT_TEST_FILE()

TEST(test_that_passes) {
    return 0;
}

TEST(test_that_fails) {
    ASSERT_EQUAL(1, 2, "this will fail")
    return 0;
}

int main(void) {
    REGISTER(test_that_passes);
    REGISTER(test_that_fails);

    RUN_TESTS()
}
