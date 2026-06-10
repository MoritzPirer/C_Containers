#include "../inc/hset/hset.h"
#include "../inc/vec/vec.h"
#include "tests.h"

#include <string.h>

#define ASSERT_STATUS(msg, expected, actual) \
    ASSERT_TRUE(msg, (expected) == (actual))

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

static bool custom_string_compare(const void* a, const void* b, size_t item_size) {
    (void) item_size;

    return strcmp(*(const char**)a, *(const char**)b) == 0;
}

void hset_init_edge_cases() {
    hset_t hset;

    ASSERT_STATUS("Init should fail with NULL self", 
        HSET_ERROR_NULL, hset_init(NULL, 8, sizeof(int), NULL));

    ASSERT_STATUS("Init should fail with 0 element size", 
        HSET_ERROR_INVALID, hset_init(&hset, 8, 0, NULL));

    ASSERT_STATUS("Init should succeed with custom comparison", 
        HSET_OK, hset_init(&hset, 4, sizeof(char*), custom_string_compare));

    hset_destroy(&hset);
}

void hset_destroy_edge_cases() {
    ASSERT_STATUS("Destroy should gracefully handle NULL pointer", 
        HSET_ERROR_NULL, hset_destroy(NULL));
}

void hset_copy_test() {
    hset_t source, copy;
    hset_init(&source, 4, sizeof(int), NULL);
    
    int val1 = 42, val2 = 84;
    hset_add(&source, &val1);
    hset_add(&source, &val2);

    ASSERT_STATUS("Copying populated set should succeed", HSET_OK, hset_copy(&source, &copy));
    ASSERT_TRUE("Copy should contain val1", hset_contains(&copy, &val1));
    ASSERT_TRUE("Copy should contain val2", hset_contains(&copy, &val2));
    ASSERT_TRUE("Copy size should match source", hset_size(&source) == hset_size(&copy));

    hset_destroy(&source);
    hset_destroy(&copy);
}

void hset_add_remove_edge_cases() {
    hset_t hset;
    hset_init(&hset, 4, sizeof(int), NULL);
    int item = 100;

    ASSERT_STATUS("Add with NULL self should fail", HSET_ERROR_NULL, hset_add(NULL, &item));
    ASSERT_STATUS("Add with NULL source should fail", HSET_ERROR_NULL, hset_add(&hset, NULL));
    ASSERT_STATUS("Remove with NULL self should fail", HSET_ERROR_NULL, hset_remove(NULL, &item));
    ASSERT_STATUS("Remove with NULL source should fail", HSET_ERROR_NULL, hset_remove(&hset, NULL));

    ASSERT_STATUS("First add should succeed", HSET_OK, hset_add(&hset, &item));
    ASSERT_TRUE("Size should be 1", hset_size(&hset) == 1);
    
    ASSERT_STATUS("Duplicate add should have no destructive effect", HSET_OK, hset_add(&hset, &item));
    ASSERT_TRUE("Size should remain 1 after duplicate add", hset_size(&hset) == 1);

    int non_existent = 999;
    ASSERT_STATUS("Removing non-existent item should not error out", HSET_OK, hset_remove(&hset, &non_existent));
    ASSERT_TRUE("Size should remain 1", hset_size(&hset) == 1);

    hset_destroy(&hset);
}

void hset_metadata_and_clear() {
    hset_t hset;
    
    ASSERT_TRUE("hset_size on NULL should be -1 (cast to size_t)", hset_size(NULL) == (size_t)-1);
    ASSERT_TRUE("hset_is_empty on NULL should be true", hset_is_empty(NULL));
    ASSERT_STATUS("hset_clear on NULL should return error", HSET_ERROR_NULL, hset_clear(NULL));

    hset_init(&hset, 4, sizeof(int), NULL);
    ASSERT_TRUE("Newly initialized set should be empty", hset_is_empty(&hset));
    ASSERT_TRUE("Newly initialized set size should be 0", hset_size(&hset) == 0);

    int items[] = {1, 2, 3};
    hset_add(&hset, &items[0]);
    hset_add(&hset, &items[1]);
    hset_add(&hset, &items[2]);

    ASSERT_FALSE("Set shouldn't be empty after adds", hset_is_empty(&hset));
    ASSERT_TRUE("Set size should be 3", hset_size(&hset) == 3);

    ASSERT_STATUS("Clear should execute perfectly", HSET_OK, hset_clear(&hset));
    ASSERT_TRUE("Set should be empty after clear", hset_is_empty(&hset));
    ASSERT_TRUE("Set size should be 0 after clear", hset_size(&hset) == 0);
    ASSERT_FALSE("Should no longer contain item 1", hset_contains(&hset, &items[0]));

    hset_destroy(&hset);
}

void hset_equals_test() {
    hset_t a, b;
    hset_init(&a, 4, sizeof(int), NULL);
    hset_init(&b, 4, sizeof(int), NULL);

    ASSERT_TRUE("Two empty sets should be equal", hset_equals(&a, &b));

    int x = 5, y = 10;
    hset_add(&a, &x);
    ASSERT_FALSE("Sets should not be equal if sizes differ", hset_equals(&a, &b));

    hset_add(&b, &x);
    ASSERT_TRUE("Sets should be equal when matching elements are added", hset_equals(&a, &b));

    hset_add(&a, &y);
    hset_add(&b, &x); // Duplicate element
    ASSERT_FALSE("Sets with matching unique capacities but different actual values shouldn't match", hset_equals(&a, &b));

    hset_destroy(&a);
    hset_destroy(&b);
}

void hset_union_test() {
    hset_t a, b, result;
    hset_init(&a, 4, sizeof(int), NULL);
    hset_init(&b, 4, sizeof(int), NULL);

    int n1 = 10, n2 = 20, n3 = 30;
    hset_add(&a, &n1);
    hset_add(&a, &n2); // a = {10, 20}
    
    hset_add(&b, &n2);
    hset_add(&b, &n3); // b = {20, 30}

    ASSERT_STATUS("Union operation should return success status", HSET_OK, hset_union(&a, &b, &result));
    
    ASSERT_TRUE("Union result should have a size of 3", hset_size(&result) == 3);
    ASSERT_TRUE("Union should contain 10", hset_contains(&result, &n1));
    ASSERT_TRUE("Union should contain 20", hset_contains(&result, &n2));
    ASSERT_TRUE("Union should contain 30", hset_contains(&result, &n3));

    hset_destroy(&a);
    hset_destroy(&b);
    hset_destroy(&result);
}

void hset_intersection_test() {
    hset_t a, b, result;
    hset_init(&a, 4, sizeof(int), NULL);
    hset_init(&b, 4, sizeof(int), NULL);

    int n1 = 1, n2 = 2, n3 = 3;
    hset_add(&a, &n1); hset_add(&a, &n2); // a = {1, 2}
    hset_add(&b, &n2); hset_add(&b, &n3); // b = {2, 3}

    ASSERT_STATUS("Intersection operation should succeed", HSET_OK, hset_intersection(&a, &b, &result));
    
    ASSERT_TRUE("Intersection size should be 1", hset_size(&result) == 1);
    ASSERT_TRUE("Intersection should contain overlap element (2)", hset_contains(&result, &n2));
    ASSERT_FALSE("Intersection should not contain 1", hset_contains(&result, &n1));

    hset_destroy(&a);
    hset_destroy(&b);
    hset_destroy(&result);
}

void hset_difference_test() {
    hset_t a, b, result;
    hset_init(&a, 4, sizeof(int), NULL);
    hset_init(&b, 4, sizeof(int), NULL);

    int n1 = 5, n2 = 10, n3 = 15;
    hset_add(&a, &n1); hset_add(&a, &n2); // a = {5, 10}
    hset_add(&b, &n2); hset_add(&b, &n3); // b = {10, 15}

    ASSERT_STATUS("Difference operation should succeed", HSET_OK, hset_difference(&a, &b, &result));

    ASSERT_TRUE("Difference size should be 1", hset_size(&result) == 1);
    ASSERT_TRUE("Difference should contain unique item from A (5)", hset_contains(&result, &n1));
    ASSERT_FALSE("Difference should not contain shared item (10)", hset_contains(&result, &n2));

    hset_destroy(&a);
    hset_destroy(&b);
    hset_destroy(&result);
}

void hset_symmetric_difference_test() {
    hset_t a, b, result;
    hset_init(&a, 4, sizeof(int), NULL);
    hset_init(&b, 4, sizeof(int), NULL);

    int n1 = 100, n2 = 200, n3 = 300;
    hset_add(&a, &n1); hset_add(&a, &n2); // a = {100, 200}
    hset_add(&b, &n2); hset_add(&b, &n3); // b = {200, 300}

    ASSERT_STATUS("Symmetric difference should succeed", HSET_OK, hset_symmetric_difference(&a, &b, &result));

    ASSERT_TRUE("Symmetric difference size should be 2", hset_size(&result) == 2);
    ASSERT_TRUE("Should contain 100", hset_contains(&result, &n1));
    ASSERT_FALSE("Should NOT contain shared 200", hset_contains(&result, &n2));
    ASSERT_TRUE("Should contain 300", hset_contains(&result, &n3));

    hset_destroy(&a);
    hset_destroy(&b);
    hset_destroy(&result);
}

void hset_sub_superset() {
    hset_t a, b;
    hset_init(&a, 4, sizeof(int), NULL);
    hset_init(&b, 4, sizeof(int), NULL);

    // Edge Case: Empty sets are subsets/supersets of each other
    ASSERT_TRUE("Empty A should be subset of Empty B", hset_is_subset_of(&a, &b));
    ASSERT_TRUE("Empty A should be superset of Empty B", hset_is_superset_of(&a, &b));

    int n1 = 10, n2 = 20;
    hset_add(&a, &n1);
    hset_add(&a, &n2); // a = {10, 20}

    hset_add(&b, &n1); // b = {10}

    ASSERT_FALSE("A {10, 20} should NOT be a subset of B {10}", hset_is_subset_of(&a, &b));
    ASSERT_TRUE("A {10, 20} SHOULD be a superset of B {10}", hset_is_superset_of(&a, &b));
    ASSERT_TRUE("B {10} SHOULD be a subset of A {10, 20}", hset_is_subset_of(&b, &a));

    // Data mismatch edge cases: Different types or comparisons
    hset_t c;
    hset_init(&c, 4, sizeof(double), NULL); // mismatching element size
    int val = 10;
    hset_add(&c, &val);

    ASSERT_FALSE("Subset evaluation should fail safely when structural metadata mismatches", hset_is_subset_of(&a, &c));

    hset_destroy(&a);
    hset_destroy(&b);
    hset_destroy(&c);
}

static bool test_condition_equals(const void* element, const void* data) {
    if (!element || !data) return false;
    return *(const int*)element == *(const int*)data;
}

static bool test_condition_is_even(const void* element, const void* data) {
    (void)data; // Unused
    if (!element) return false;
    printf("element is %d\n", *(const int*) element);
    return (*(const int*)element) % 2 == 0;
}

void test_hset_to_vec() {
    hset_t hset;
    vec_t vec;
    hset_init(&hset, 4, sizeof(int), NULL);

    ASSERT_TRUE("Exporting empty set should return HSET_OK", hset_to_vec(&hset, &vec) == HSET_OK);
    vec_destroy(&vec);

    int values[] = {10, 20, 30};
    hset_add(&hset, &values[0]);
    hset_add(&hset, &values[1]);
    hset_add(&hset, &values[2]);

    ASSERT_TRUE("Exporting populated set should return HSET_OK", hset_to_vec(&hset, &vec) == HSET_OK);

    ASSERT_TRUE("Set should contain all elements exported to vec", hset_contains_all(&hset, &vec));

    vec_destroy(&vec);
    hset_destroy(&hset);
}

void test_hset_add_all_and_remove_all() {
    hset_t hset;
    vec_t vec;
    hset_init(&hset, 4, sizeof(int), NULL);
    vec_init(&vec, 0, sizeof(int));

    int items[] = {42, 42, 99, 100}; 
    vec_push_back(&vec, &items[0]);
    vec_push_back(&vec, &items[1]);
    vec_push_back(&vec, &items[2]);

    ASSERT_TRUE("add_all should return HSET_OK", hset_add_all(&hset, &vec) == HSET_OK);
    ASSERT_TRUE("Set size should be 2 (duplicates ignored)", hset_size(&hset) == 2);
    ASSERT_TRUE("Set should contain 42", hset_contains(&hset, &items[0]));
    ASSERT_TRUE("Set should contain 99", hset_contains(&hset, &items[2]));

    vec_t remove_vec;
    vec_init(&remove_vec, 4, sizeof(int));
    int rem_items[] = {42, 888}; 
    vec_push_back(&remove_vec, &rem_items[0]);
    vec_push_back(&remove_vec, &rem_items[1]);

    ASSERT_TRUE("remove_all should return HSET_OK", hset_remove_all(&hset, &remove_vec) == HSET_OK);
    ASSERT_FALSE("Set should no longer contain 42", hset_contains(&hset, &rem_items[0]));
    ASSERT_TRUE("Set should still contain 99", hset_contains(&hset, &items[2]));
    ASSERT_TRUE("Set size should scale down to 1", hset_size(&hset) == 1);

    vec_destroy(&vec);
    vec_destroy(&remove_vec);
    hset_destroy(&hset);
}

void test_hset_contains_all_and_any() {
    hset_t hset;
    vec_t vec;
    hset_init(&hset, 4, sizeof(int), NULL);
    vec_init(&vec, 0, sizeof(int));

    int n1 = 5, n2 = 10, n3 = 15;
    hset_add(&hset, &n1);
    hset_add(&hset, &n2); // Set contains {5, 10}

    ASSERT_TRUE("contains_all on empty vector should pass/be true", hset_contains_all(&hset, &vec));
    ASSERT_FALSE("contains_any on empty vector should be false", hset_contains_any(&hset, &vec));

    vec_push_back(&vec, &n2);
    vec_push_back(&vec, &n3); 

    ASSERT_FALSE("contains_all should be false (15 is missing)", hset_contains_all(&hset, &vec));
    ASSERT_TRUE("contains_any should be true (10 matches)", hset_contains_any(&hset, &vec));

    vec_t matching_vec;
    vec_init(&matching_vec, 0, sizeof(int));
    vec_push_back(&matching_vec, &n1);
    vec_push_back(&matching_vec, &n2);

    ASSERT_TRUE("contains_all should be true for exact sub-matches", hset_contains_all(&hset, &matching_vec));

    vec_destroy(&vec);
    vec_destroy(&matching_vec);
    hset_destroy(&hset);
}

void test_hset_any_all_none() {
    hset_t hset;
    hset_init(&hset, 4, sizeof(int), NULL);

    int target = 20;

    ASSERT_FALSE("any should return false on empty set", hset_any(&hset, test_condition_equals, &target));
    ASSERT_TRUE("all should return true on empty set (vacuous truth)", hset_all(&hset, test_condition_equals, &target));
    ASSERT_TRUE("none should return true on empty set", hset_none(&hset, test_condition_equals, &target));

    int o1 = 1, o2 = 3, o3 = 5;
    hset_add(&hset, &o1);
    hset_add(&hset, &o2);
    hset_add(&hset, &o3);

    ASSERT_FALSE("any should be false (no evens)", hset_any(&hset, test_condition_is_even, NULL));
    ASSERT_FALSE("all should be false (no evens)", hset_all(&hset, test_condition_is_even, NULL));
    ASSERT_TRUE("none should be true (all odds)", hset_none(&hset, test_condition_is_even, NULL));

    int e1 = 4;
    hset_add(&hset, &e1);

    ASSERT_TRUE("any should now be true (4 is even)", hset_any(&hset, test_condition_is_even, NULL));
    ASSERT_FALSE("all should still be false (mixed content)", hset_all(&hset, test_condition_is_even, NULL));
    ASSERT_FALSE("none should now be false (4 is even)", hset_none(&hset, test_condition_is_even, NULL));

    hset_clear(&hset);
    int e2 = 6, e3 = 8;
    hset_add(&hset, &e1);
    hset_add(&hset, &e2);
    hset_add(&hset, &e3);

    ASSERT_TRUE("all should be true on pure even dataset", hset_all(&hset, test_condition_is_even, NULL));

    hset_destroy(&hset);
}

void test_hset_filter() {
    hset_t hset;
    hset_t filtered;
    hset_init(&hset, 5, sizeof(int), NULL);

    hset_debug(&hset);
    int elements[] = {1, 2, 3, 4, 5, 6};
    for (int i = 0; i < 6; i++) {
        hset_add(&hset, &elements[i]);
    }

    hset_debug(&hset);
    ASSERT_TRUE("Filter with NULL self returns error", hset_filter(NULL, test_condition_is_even, &filtered, NULL) == HSET_ERROR_NULL);
    ASSERT_TRUE("Filter with NULL destination returns error", hset_filter(&hset, test_condition_is_even, NULL, NULL) == HSET_ERROR_NULL);

    ASSERT_TRUE("Valid filter call returns HSET_OK", hset_filter(&hset, test_condition_is_even, &filtered, NULL) == HSET_OK);

    hset_debug(&hset);
    hset_debug(&filtered);
    ASSERT_TRUE("Filtered set should have size 3", hset_size(&filtered) == 3);
    ASSERT_TRUE("Filtered set contains 2", hset_contains(&filtered, &elements[1]));
    ASSERT_TRUE("Filtered set contains 4", hset_contains(&filtered, &elements[3]));
    ASSERT_TRUE("Filtered set contains 6", hset_contains(&filtered, &elements[5]));
    ASSERT_FALSE("Filtered set does not contain 1", hset_contains(&filtered, &elements[0]));

    hset_destroy(&hset);
    hset_destroy(&filtered);
}

void hset_vector_and_predicate_tests() {
    printf("--- RUNNING VEC INTEROP TESTS ---\n");
    RUN_TEST(test_hset_to_vec);
    RUN_TEST(test_hset_add_all_and_remove_all);
    RUN_TEST(test_hset_contains_all_and_any);

    printf("--- RUNNING PREDICATE EVALUATION TESTS ---\n");
    RUN_TEST(test_hset_any_all_none);
    RUN_TEST(test_hset_filter);
    
    printf("\n");
}

void hset_tests() {
    printf("--- RUNNING HSET TESTS ---\n");
    RUN_TEST(hset_basic);
    RUN_TEST(hset_grow);
    RUN_TEST(hset_init_edge_cases);
    RUN_TEST(hset_destroy_edge_cases);
    RUN_TEST(hset_copy_test);
    RUN_TEST(hset_metadata_and_clear);
    RUN_TEST(hset_add_remove_edge_cases);
    RUN_TEST(hset_equals_test);
    RUN_TEST(hset_union_test);
    RUN_TEST(hset_intersection_test);
    RUN_TEST(hset_difference_test);
    RUN_TEST(hset_symmetric_difference_test);
    RUN_TEST(hset_sub_superset);
    RUN_TEST(test_hset_to_vec);
    RUN_TEST(test_hset_add_all_and_remove_all);
    RUN_TEST(test_hset_contains_all_and_any);

    RUN_TEST(test_hset_any_all_none);
    RUN_TEST(test_hset_filter);

    printf("\n--- ALL TESTS COMPLETED SUCCESSFULLY ---\n");
}
