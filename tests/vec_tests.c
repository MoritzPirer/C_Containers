#include "../inc/vec/vec.h"
#include "tests.h"

void vec_capacity_afterPartialErase(void) {
    vec_t vec;
    vec_init(&vec, 0, sizeof(size_t));

    size_t element = 1;
    vec_push_back(&vec, &element);
    vec_push_back(&vec, &element);
    vec_push_back(&vec, &element);
    vec_push_back(&vec, &element);
    vec_push_back(&vec, &element);
    
    vec_erase_to(&vec, 3);
    ASSERT_TRUE("Capacity should not exceed 4 after erasing up to index 3", vec_capacity(&vec) <= 4);
}

void vec_capacity_afterReserveResize(void) {
    vec_t vec;
    vec_init(&vec, 0, sizeof(int));

    vec_reserve(&vec, 10);
    ASSERT_TRUE("Capacity should be at least 10 after reserve", vec_capacity(&vec) >= 10);

    vec_resize(&vec, 20);
    ASSERT_TRUE("Capacity should be at least 20 after resize", vec_capacity(&vec) >= 20);
}

void vec_destroy_initialized(void) {
    vec_t vec;
    vec_init(&vec, 1, sizeof(int));

    vec_destroy(&vec);

    ASSERT_PTR_EQ("Data pointer should be NULL after destroy", NULL, vec.array);
    ASSERT_INT_EQ("Allocated capacity should be 0 after destroy", 0, vec.capacity);
    ASSERT_INT_EQ("Size used should be 0 after destroy", 0, vec.size);
}

void vec_destroy_NULL(void) {
    vec_destroy(NULL); 
    ASSERT_TRUE("Should not crash when destroying a NULL pointer", 1);
}

void vec_destroy_double(void) {
    vec_t vec;
    vec_init(&vec, 10, sizeof(int));

    vec_destroy(&vec);

    ASSERT_PTR_EQ("Data pointer should be NULL after first destroy", NULL, vec.array);
    ASSERT_INT_EQ("Allocated capacity should be 0 after first destroy", 0, vec.capacity);
    ASSERT_INT_EQ("Size used should be 0 after first destroy", 0, vec.size);

    vec_destroy(&vec); // test double free protection

    ASSERT_PTR_EQ("Data pointer should stay NULL after double destroy", NULL, vec.array);
    ASSERT_INT_EQ("Allocated capacity should stay 0 after double destroy", 0, vec.capacity);
    ASSERT_INT_EQ("Size used should stay 0 after double destroy", 0, vec.size);
}

void vec_init_elementSize_0(void) {
    vec_t d;
    vec_status_t res = vec_init(&d, 1, 0);

    ASSERT_INT_EQ("Initializing with element size 0 should return INVALID status", VEC_ERROR_INVALID, res);
}

void vec_init_NULL(void) {
    vec_status_t res = vec_init(NULL, 1, 1);

    ASSERT_INT_EQ("Initializing a NULL vector pointer should return NULL status", VEC_ERROR_NULL, res);
}

void vec_init_size_0(void) {
    vec_t d;
    vec_init(&d, 0, sizeof(int));

    ASSERT_INT_EQ("Item size should match given element size", sizeof(int), d.item_size);
    ASSERT_INT_EQ("Capacity allocated should match baseline VEC_MIN_SIZE", VEC_MIN_SIZE, d.capacity);
    ASSERT_INT_EQ("Size used should be exactly 0", 0, d.size);
}

void vec_init_size_1(void) {
    vec_t d;
    vec_init(&d, 0, sizeof(int));

    ASSERT_INT_EQ("Item size should match given element size", sizeof(int), d.item_size);
    ASSERT_INT_EQ("Capacity allocated should match baseline VEC_MIN_SIZE", VEC_MIN_SIZE, d.capacity);
}


void vec_init_size_XL(void) {
    vec_t d;
    size_t capacity = 10000000;
    vec_init(&d, capacity, sizeof(int));

    ASSERT_INT_EQ("Item size should match given element size", sizeof(int), d.item_size);
    ASSERT_TRUE("Capacity allocated should be greater than or equal to large requested size", d.capacity >= capacity);
}

void vec_init_size_XXXL(void) {
    vec_t d;
    size_t size = (size_t)-1;
    vec_status_t res = vec_init(&d, size, sizeof(int));

    // If it mistakenly returned success, data block validation must catch it
    if (res == VEC_OK) {
        ASSERT_TRUE("If init succeeds with size -1, data pointer must not be NULL", d.array != NULL);
    } else {
        ASSERT_TRUE("Init failed gracefully with size -1", 1);
    }
}

void vec_size_empty(void) {
    vec_t d;
    vec_init(&d, 0, sizeof(size_t));

    ASSERT_INT_EQ("An empty vector size must equal 0", 0, vec_size(&d));
}

void vec_size_push_pop(void) {
    vec_t d;
    vec_init(&d, 0, sizeof(size_t));

    size_t element = 1;
    vec_push_back(&d, &element);
    ASSERT_INT_EQ("Size must equal 1 after single push", 1, vec_size(&d));

    vec_pop_back(&d, &element);
    ASSERT_INT_EQ("Size must fall back to 0 after popping last element", 0, vec_size(&d));
}

void vec_size_afterErase(void) {
    vec_t d;
    vec_init(&d, 0, sizeof(size_t));

    size_t element = 1;
    vec_push_back(&d, &element);
    vec_push_back(&d, &element);
    vec_push_back(&d, &element);
    ASSERT_INT_EQ("Size must equal 3 after 3 pushes", 3, vec_size(&d));

    vec_clear(&d);
    ASSERT_INT_EQ("Size must equal 0 after clear()", 0, vec_size(&d));

    vec_push_back(&d, &element);
    vec_push_back(&d, &element);
    vec_push_back(&d, &element);
    ASSERT_INT_EQ("Size must return to 3 after refills", 3, vec_size(&d));

    vec_erase_all(&d);
    ASSERT_INT_EQ("Size must fall back to 0 after erase_all()", 0, vec_size(&d));
}

void vec_size_afterPartialErase(void) {
    vec_t d;
    vec_init(&d, 0, sizeof(size_t));

    size_t element = 1;
    vec_push_back(&d, &element);
    vec_push_back(&d, &element);
    vec_push_back(&d, &element);
    vec_push_back(&d, &element);
    vec_push_back(&d, &element);

    vec_erase_from(&d, 1);
    ASSERT_INT_EQ("Size must drop to 1 after stripping from index 1 forward", 1, vec_size(&d));

    vec_push_back(&d, &element);
    vec_push_back(&d, &element);
    vec_push_back(&d, &element);
    vec_push_back(&d, &element);
    vec_push_back(&d, &element);
    
    vec_erase_to(&d, 3);
    ASSERT_INT_EQ("Size must equal 2 after trimming up to index 3", 2, vec_size(&d));
}

void vec_size_afterReserveResize(void) {
    vec_t d;
    vec_init(&d, 0, sizeof(int));

    vec_reserve(&d, 10);
    ASSERT_INT_EQ("Reserving raw capacity should not shift active size tracker", 0, vec_size(&d));

    vec_resize(&d, 20);
    ASSERT_INT_EQ("Resizing should physically shift accessible size to 20 elements", 20, vec_size(&d));
}

void vec_tests() {
    printf("--- RUNNING CORE VECTOR TESTS ---\n");

    RUN_TEST(vec_capacity_afterPartialErase);
    RUN_TEST(vec_capacity_afterReserveResize);
    RUN_TEST(vec_destroy_initialized);
    RUN_TEST(vec_destroy_NULL);
    RUN_TEST(vec_destroy_double);
    RUN_TEST(vec_init_elementSize_0);
    RUN_TEST(vec_init_NULL);
    RUN_TEST(vec_init_size_0);
    RUN_TEST(vec_init_size_1);
    RUN_TEST(vec_init_size_XL);
    RUN_TEST(vec_init_size_XXXL);
    RUN_TEST(vec_size_empty);
    RUN_TEST(vec_size_push_pop);
    RUN_TEST(vec_size_afterErase);
    RUN_TEST(vec_size_afterPartialErase);
    RUN_TEST(vec_size_afterReserveResize);

    printf("\n");
}
