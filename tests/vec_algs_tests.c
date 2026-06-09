#include "../inc/vec/vec_algs.h"
#include "tests.h"
#include <stddef.h>

void vec_algs_find_first_one_option(void) {
    vec_t d;
    vec_init(&d, 0, sizeof(size_t));

    for (size_t i = 0; i < 10; i++) {
        vec_push_back(&d, &i);
    }
    size_t temp;
    size_t target = 2;
    vec_status_t res = vec_find_first(&d, vec_default_condition, &temp, &target);
    
    ASSERT_INT_EQ("Finding existing element should return VEC_OK", VEC_OK, res);
    ASSERT_INT_EQ("Found value index should exactly match element location", 2, temp);

    vec_destroy(&d);
}

void vec_algs_find_first_two_options(void) {
    vec_t d;
    vec_init(&d, 0, sizeof(size_t));

    for (size_t i = 0; i < 10; i++) {
        vec_push_back(&d, &i);
    }
    size_t temp = 2;
    vec_push_back(&d, &temp);

    size_t target = 2;
    vec_status_t res = vec_find_first(&d, vec_default_condition, &temp, &target);
    
    ASSERT_INT_EQ("Finding existing item with multiple matches should return VEC_OK", VEC_OK, res);
    ASSERT_INT_EQ("find_first should locate the earliest matched index occurrence", 2, temp);

    vec_destroy(&d);
}

void vec_algs_find_first_no_option(void) {
    vec_t d;
    vec_init(&d, 0, sizeof(size_t));

    for (size_t i = 0; i < 10; i++) {
        vec_push_back(&d, &i);
    }
    size_t temp;
    size_t target = 15;
    vec_status_t res = vec_find_first(&d, vec_default_condition, &temp, &target);
    
    ASSERT_INT_EQ("Searching for out-of-bounds target must return VEC_NOT_FOUND", VEC_NOT_FOUND, res);

    vec_destroy(&d);
}

void vec_algs_find_last_one_option(void) {
    vec_t d;
    vec_init(&d, 0, sizeof(size_t));

    for (size_t i = 0; i < 10; i++) {
        vec_push_back(&d, &i);
    }
    size_t temp;
    size_t target = 2;
    vec_status_t res = vec_find_last(&d, vec_default_condition, &temp, &target);
    
    ASSERT_INT_EQ("Finding last unique element should return VEC_OK", VEC_OK, res);
    ASSERT_INT_EQ("Single item search position should resolve correctly", 2, temp);

    vec_destroy(&d);
}

void vec_algs_find_last_two_options(void) {
    vec_t d;
    vec_init(&d, 0, sizeof(size_t));

    for (size_t i = 0; i < 10; i++) {
        vec_push_back(&d, &i);
    }
    size_t temp = 2;
    vec_push_back(&d, &temp);

    size_t target = 2;
    vec_status_t res = vec_find_last(&d, vec_default_condition, &temp, &target);
    
    ASSERT_INT_EQ("Finding duplicate item last occurrence should return VEC_OK", VEC_OK, res);
    ASSERT_INT_EQ("find_last should track the highest indexed instance", 10, temp);

    vec_destroy(&d);
}

void vec_algs_find_last_no_option(void) {
    vec_t d;
    vec_init(&d, 0, sizeof(size_t));

    for (size_t i = 0; i < 10; i++) {
        vec_push_back(&d, &i);
    }
    size_t temp;
    size_t target = 15;
    vec_status_t res = vec_find_last(&d, vec_default_condition, &temp, &target);
    
    ASSERT_INT_EQ("Searching backwards for an absent target must return VEC_NOT_FOUND", VEC_NOT_FOUND, res);

    vec_destroy(&d);
}

void vec_algs_find_first_last_empty(void) {
    vec_t d;
    vec_init(&d, 0, sizeof(size_t));
    size_t temp = 1;
    
    ASSERT_INT_EQ("find_first on cold empty vector must evaluate to VEC_NOT_FOUND", VEC_NOT_FOUND, vec_find_first(&d, vec_default_condition, &temp, &temp));
    ASSERT_INT_EQ("find_last on cold empty vector must evaluate to VEC_NOT_FOUND", VEC_NOT_FOUND, vec_find_last(&d, vec_default_condition, &temp, &temp));

    vec_destroy(&d);
}

void vec_algs_binary_search_simple(void) {
    vec_t d;
    vec_init(&d, 0, sizeof(size_t));

    for (size_t i = 0; i < 10; i++) {
        vec_push_back(&d, &i);
    }
    size_t temp;
    size_t target = 2;
    vec_status_t res = vec_binary_search(&d, vec_default_ordering, &temp, &target);
    
    ASSERT_INT_EQ("Binary searching sorted range should return VEC_OK", VEC_OK, res);
    ASSERT_INT_EQ("Binary search should yield the precise target location", 2, temp);

    vec_destroy(&d);
}

void vec_algs_binary_search_empty(void) {
    vec_t d;
    vec_init(&d, 0, sizeof(size_t));

    size_t temp;
    size_t target = 2;
    vec_status_t res = vec_binary_search(&d, vec_default_ordering, &temp, &target);
    
    ASSERT_INT_EQ("Binary search over an empty layout must yield VEC_NOT_FOUND", VEC_NOT_FOUND, res);

    vec_destroy(&d);
}

void vec_algs_binary_search_small(void) {
    vec_t d;
    vec_init(&d, 0, sizeof(size_t));

    for (size_t i = 0; i < 3; i++) {
        vec_push_back(&d, &i);
    }

    size_t temp;
    size_t target = 2;
    vec_status_t res = vec_binary_search(&d, vec_default_ordering, &temp, &target);
    
    ASSERT_INT_EQ("Binary searching bounded micro-range should return VEC_OK", VEC_OK, res);
    ASSERT_INT_EQ("Target index location match inside tiny array must be accurate", 2, temp);

    vec_destroy(&d);
}

void vec_algs_is_sorted_asc_simple(void) {
    vec_t d;
    vec_init(&d, 0, sizeof(size_t));

    for (size_t i = 0; i < 10; i++) {
        vec_push_back(&d, &i);
    }

    ASSERT_TRUE("Sequential loop increments must resolve as sorted ascending", vec_is_sorted_asc(d, vec_default_ordering));

    vec_destroy(&d);
}

void vec_algs_is_sorted_empty(void) {
    vec_t d;
    vec_init(&d, 0, sizeof(size_t));

    ASSERT_TRUE("Empty structure collection evaluates to vacuously sorted", vec_is_sorted_asc(d, vec_default_ordering));

    vec_destroy(&d);
}

void vec_algs_is_sorted_asc_all_same(void) {
    vec_t d;
    vec_init(&d, 0, sizeof(size_t));
    size_t val = 10;
    for (size_t i = 0; i < 10; i++) {
        vec_push_back(&d, &val);
    }

    ASSERT_TRUE("A uniform constant series should qualify as sorted ascending", vec_is_sorted_asc(d, vec_default_ordering));

    vec_destroy(&d);
}

void vec_algs_is_sorted_asc_false(void) {
    vec_t d;
    vec_init(&d, 0, sizeof(size_t));

    for (size_t i = 20; i > 10; i--) {
        vec_push_back(&d, &i);
    }

    ASSERT_FALSE("Strict descending input profile must fail ascending verification checks", vec_is_sorted_asc(d, vec_default_ordering));

    vec_destroy(&d);
}

void vec_algs_is_sorted_desc_simple(void) {
    vec_t d;
    vec_init(&d, 0, sizeof(size_t));

    for (size_t i = 20; i > 10; i--) {
        vec_push_back(&d, &i);
    }

    ASSERT_TRUE("Iterative array step decrements should track cleanly as sorted descending", vec_is_sorted_desc(d, vec_default_ordering));

    vec_destroy(&d);
}

void vec_algs_is_sorted_desc_all_same(void) {
    vec_t d;
    vec_init(&d, 0, sizeof(size_t));
    size_t val = 10;
    for (size_t i = 0; i < 10; i++) {
        vec_push_back(&d, &val);
    }

    ASSERT_TRUE("A uniform constant series should qualify as sorted descending", vec_is_sorted_desc(d, vec_default_ordering));

    vec_destroy(&d);
}

void vec_algs_is_sorted_desc_false(void) {
    vec_t d;
    vec_init(&d, 0, sizeof(size_t));

    for (size_t i = 0; i < 10; i++) {
        vec_push_back(&d, &i);
    }

    ASSERT_FALSE("Standard ascending sequences must fail descending validation sweeps", vec_is_sorted_desc(d, vec_default_ordering));

    vec_destroy(&d);
}

void vec_algs_reverse_basic(void) {
    vec_t vec;
    vec_range_to(&vec, 5);
    vec_reverse(&vec);

    size_t expected[] = {4, 3, 2, 1, 0};
    ASSERT_INT_EQ("Reversed elements tracking bounds must match source count", 5, vec_size(&vec));

    for (size_t i = 0; i < 5; i++) {
        size_t value;
        ASSERT_INT_EQ("Retrieving inverse mapped index must return safely", VEC_OK, vec_get(&vec, i, &value));
        ASSERT_INT_EQ("Element at flipped index alignment tracking matches expectations", expected[i], value);
    }
    
    vec_destroy(&vec);
}

void vec_algs_range_simple_forward(void) {
    vec_t vec;
    vec_init(&vec, 0, sizeof(size_t));

    ASSERT_INT_EQ("Building simple explicit step range returns VEC_OK", VEC_OK, vec_range_from_to_step(&vec, 0, 5, 1));

    size_t expected[] = {0, 1, 2, 3, 4};
    ASSERT_INT_EQ("Dispatched vector sequence length validation fits boundary", 5, vec_size(&vec));

    for (size_t i = 0; i < 5; i++) {
        size_t value;
        ASSERT_INT_EQ("Reading sequence slot status reports VEC_OK", VEC_OK, vec_get(&vec, i, &value));
        ASSERT_INT_EQ("Generated slot variable value must track counter accurately", expected[i], value);
    }

    vec_destroy(&vec);
}

void vec_algs_range_forward_step_two(void) {
    vec_t d;
    vec_init(&d, 0, sizeof(size_t));

    ASSERT_INT_EQ("Instantiating positive multi-stride ranges returns VEC_OK", VEC_OK, vec_range_from_to_step(&d, 0, 10, 2));

    size_t expected[] = {0, 2, 4, 6, 8};
    ASSERT_INT_EQ("Stride step-calculated vector bounds verification", 5, vec_size(&d));

    for (size_t i = 0; i < 5; i++) {
        size_t value;
        ASSERT_INT_EQ("Reading calculated interval bounds returns VEC_OK", VEC_OK, vec_get(&d, i, &value));
        ASSERT_INT_EQ("Array space tracking mapping matching target stride increments", expected[i], value);
    }

    vec_destroy(&d);
}

void vec_algs_range_backward(void) {
    vec_t d;
    vec_init(&d, 0, sizeof(size_t));

    ASSERT_INT_EQ("Executing backward single step range returns VEC_OK", VEC_OK, vec_range_from_to_step(&d, 5, 0, -1));

    size_t expected[] = {5, 4, 3, 2, 1};
    ASSERT_INT_EQ("Negative trajectory data stack sizing check", 5, vec_size(&d));

    for (size_t i = 0; i < 5; i++) {
        size_t value;
        ASSERT_INT_EQ("Querying internal descending cells returns VEC_OK", VEC_OK, vec_get(&d, i, &value));
        ASSERT_INT_EQ("Enforced descending array items output synchronization check", expected[i], value);
    }

    vec_destroy(&d);
}

void vec_algs_range_backward_step_two(void) {
    vec_t d;
    vec_init(&d, 0, sizeof(size_t));

    ASSERT_INT_EQ("Executing stride-skipped reverse iterations returns VEC_OK", VEC_OK, vec_range_from_to_step(&d, 10, 0, -2));

    size_t expected[] = {10, 8, 6, 4, 2};
    ASSERT_INT_EQ("Sizing tracking evaluation for complex descending configurations", 5, vec_size(&d));

    for (size_t i = 0; i < 5; i++) {
        size_t value;
        ASSERT_INT_EQ("Extracting strided reversed index states returns VEC_OK", VEC_OK, vec_get(&d, i, &value));
        ASSERT_INT_EQ("Comparing data storage sequence index to negative offsets value", expected[i], value);
    }

    vec_destroy(&d);
}

void vec_algs_range_empty(void) {
    vec_t d;
    vec_init(&d, 0, sizeof(size_t));

    ASSERT_INT_EQ("Setting identical start and stop thresholds returns VEC_OK", VEC_OK, vec_range_from_to_step(&d, 3, 3, 1));
    ASSERT_INT_EQ("Null sequence boundaries produce a collection size of zero", 0, vec_size(&d));

    vec_destroy(&d);
}

void vec_algs_range_zero_step(void) {
    vec_t d;
    vec_init(&d, 0, sizeof(size_t));

    ASSERT_INT_EQ("Injecting step increments of 0 must register as VEC_ERROR_INVALID", VEC_ERROR_INVALID, vec_range_from_to_step(&d, 0, 5, 0));

    vec_destroy(&d);
}

void vec_algs_range_invalid_negative_step_forward(void) {
    vec_t d;
    vec_init(&d, 0, sizeof(size_t));

    ASSERT_INT_EQ("Positive tracking direction combined with negative steps is an invalid operation", VEC_ERROR_INVALID, vec_range_from_to_step(&d, 0, 5, -1));

    vec_destroy(&d);
}

void vec_algs_range_invalid_positive_step_backward(void) {
    vec_t d;
    vec_init(&d, 0, sizeof(size_t));

    ASSERT_INT_EQ("Negative tracking direction combined with positive steps is an invalid operation", VEC_ERROR_INVALID, vec_range_from_to_step(&d, 5, 0, 1));

    vec_destroy(&d);
}

void vec_algs_range_stop_exclusive(void) {
    vec_t d;
    vec_init(&d, 0, sizeof(size_t));

    ASSERT_INT_EQ("Uneven step allocation boundary evaluation execution returns VEC_OK", VEC_OK, vec_range_from_to_step(&d, 0, 5, 3));

    size_t expected[] = {0, 3};
    ASSERT_INT_EQ("Exclusive range limits shouldn't count boundary overflows", 2, vec_size(&d));

    for (size_t i = 0; i < 2; i++) {
        size_t value;
        ASSERT_INT_EQ("Extracting index data properties returns VEC_OK", VEC_OK, vec_get(&d, i, &value));
        ASSERT_INT_EQ("Verifying items dropped beyond exclusive bounds step parameters", expected[i], value);
    }

    vec_destroy(&d);
}

void vec_algs_range_null_self(void) {
    ASSERT_INT_EQ("Directly referencing NULL vector pointer context produces error flag", VEC_ERROR_NULL, vec_range_from_to_step(NULL, 0, 5, 1));
}

void vec_algs_get_intersection_basic(void) {
    vec_t a, b, out;
    vec_init(&a, 0, sizeof(int));
    vec_init(&b, 0, sizeof(int));

    int av[] = {1, 2, 3, 4, 5};
    int bv[] = {3, 4, 5, 6, 7};

    for (int i = 0; i < 5; i++) {
        vec_push_back(&a, &av[i]);
        vec_push_back(&b, &bv[i]);
    }

    ASSERT_INT_EQ("Intersecting overlapping standard data sets returns VEC_OK", VEC_OK, vec_get_intersection(&a, &b, vec_default_ordering, &out));
    ASSERT_INT_EQ("Overlapping set items sizing outcome metric tracking", 3, vec_size(&out));

    int expected[] = {3, 4, 5};
    for (int i = 0; i < 3; i++) {
        int v;
        vec_get(&out, i, &v);
        ASSERT_INT_EQ("Verifying standard intersecting indices extraction elements", expected[i], v);
    }

    vec_destroy(&a);
    vec_destroy(&b);
    vec_destroy(&out);
}

void vec_algs_get_intersection_none(void) {
    vec_t a, b, out;
    vec_init(&a, 0, sizeof(int));
    vec_init(&b, 0, sizeof(int));

    int av[] = {1, 2, 3};
    int bv[] = {4, 5, 6};

    for (int i = 0; i < 3; i++) {
        vec_push_back(&a, &av[i]);
        vec_push_back(&b, &bv[i]);
    }

    ASSERT_INT_EQ("Intersecting disjoint arrays returns VEC_OK", VEC_OK, vec_get_intersection(&a, &b, vec_default_ordering, &out));
    ASSERT_TRUE("Disjoint collections must evaluate to empty output sets", vec_is_empty(&out));

    vec_destroy(&a);
    vec_destroy(&b);
    vec_destroy(&out);
}

void vec_algs_get_intersection_left_empty(void) {
    vec_t a, b, out;
    vec_init(&a, 0, sizeof(int));
    vec_init(&b, 0, sizeof(int));

    int v = 1;
    vec_push_back(&b, &v);

    ASSERT_INT_EQ("Evaluating intersection configurations where left side is zeroed returns VEC_OK", VEC_OK, vec_get_intersection(&a, &b, vec_default_ordering, &out));
    ASSERT_TRUE("Intersections involving a clean empty baseline side remain empty", vec_is_empty(&out));

    vec_destroy(&a);
    vec_destroy(&b);
    vec_destroy(&out);
}

void vec_algs_get_intersection_both_empty(void) {
    vec_t a, b, out;
    vec_init(&a, 0, sizeof(int));
    vec_init(&b, 0, sizeof(int));

    ASSERT_INT_EQ("Evaluating double blank cross-intersections returns VEC_OK", VEC_OK, vec_get_intersection(&a, &b, vec_default_ordering, &out));
    ASSERT_TRUE("Intersection of dual empty parameters remains strictly empty", vec_is_empty(&out));

    vec_destroy(&a);
    vec_destroy(&b);
    vec_destroy(&out);
}

void vec_algs_get_intersection_with_duplicates(void) {
    vec_t a, b, out;
    vec_init(&a, 0, sizeof(int));
    vec_init(&b, 0, sizeof(int));

    int av[] = {1, 2, 2, 3, 3, 3};
    int bv[] = {2, 2, 3, 4};

    for (int i = 0; i < 6; i++) vec_push_back(&a, &av[i]);
    for (int i = 0; i < 4; i++) vec_push_back(&b, &bv[i]);

    ASSERT_INT_EQ("Intersecting elements carrying overlapping multiplicities returns VEC_OK", VEC_OK, vec_get_intersection(&a, &b, vec_default_ordering, &out));
    ASSERT_INT_EQ("Intersection sizing for nested array multi-matches", 2, vec_size(&out));

    int e0, e1;
    vec_get(&out, 0, &e0);
    vec_get(&out, 1, &e1);

    ASSERT_INT_EQ("Duplicated segment intersection tracking index validation point 0", 2, e0);
    ASSERT_INT_EQ("Duplicated segment intersection tracking index validation point 1", 3, e1);

    vec_destroy(&a);
    vec_destroy(&b);
    vec_destroy(&out);
}

void vec_algs_get_intersection_identical(void) {
    vec_t a, b, out;
    vec_init(&a, 0, sizeof(int));
    vec_init(&b, 0, sizeof(int));

    int v[] = {1, 2, 3};

    for (int i = 0; i < 3; i++) {
        vec_push_back(&a, &v[i]);
        vec_push_back(&b, &v[i]);
    }

    ASSERT_INT_EQ("Intersecting perfectly mirroring matching layouts returns VEC_OK", VEC_OK, vec_get_intersection(&a, &b, vec_default_ordering, &out));
    ASSERT_INT_EQ("Intersection count tracking over identical arrays must equal source parameters", 3, vec_size(&out));

    vec_destroy(&a);
    vec_destroy(&b);
    vec_destroy(&out);
}

void vec_algs_get_intersection_null_args(void) {
    vec_t a;
    vec_init(&a, 0, sizeof(int));

    ASSERT_INT_EQ("Passing NULL into input parameter 1 returns error token", VEC_ERROR_NULL, vec_get_intersection(NULL, &a, vec_default_ordering, &a));
    ASSERT_INT_EQ("Passing NULL into input parameter 2 returns error token", VEC_ERROR_NULL, vec_get_intersection(&a, NULL, vec_default_ordering, &a));
    ASSERT_INT_EQ("Passing NULL into allocation target parameter 3 returns error token", VEC_ERROR_NULL, vec_get_intersection(&a, &a, vec_default_ordering, NULL));

    vec_destroy(&a);
}

void vec_algs_get_intersection_unsorted_input(void) {
    vec_t a, b, out;
    vec_init(&a, 0, sizeof(int));
    vec_init(&b, 0, sizeof(int));

    int av[] = {3, 1, 2}; 
    int bv[] = {1, 2, 3};

    for (int i = 0; i < 3; i++) {
        vec_push_back(&a, &av[i]);
        vec_push_back(&b, &bv[i]);
    }

    ASSERT_INT_EQ("Running intersections over unsorted sets must cause input state faults", VEC_ERROR_INVALID, vec_get_intersection(&a, &b, vec_default_ordering, &out));

    vec_destroy(&a);
    vec_destroy(&b);
}

void vec_algs_get_intersection_descending(void) {
    vec_t left, right, out;
    vec_init(&left, 0, sizeof(int));
    vec_init(&right, 0, sizeof(int));

    int lv[] = {9, 7, 5, 3, 1};
    int rv[] = {8, 7, 6, 5, 4};

    for (int i = 0; i < 5; i++) {
        vec_push_back(&left, &lv[i]);
        vec_push_back(&right, &rv[i]);
    }

    ASSERT_INT_EQ("Executing set intersections configured under descending layouts returns VEC_OK", VEC_OK, vec_get_intersection(&left, &right, vec_default_ordering, &out));
    ASSERT_INT_EQ("Descending intersection tracking count configuration bounds", 2, vec_size(&out));

    int v0, v1;
    vec_get(&out, 0, &v0);
    vec_get(&out, 1, &v1);

    ASSERT_INT_EQ("Verifying descending order intersect cell contents 0", 7, v0);
    ASSERT_INT_EQ("Verifying descending order intersect cell contents 1", 5, v1);

    vec_destroy(&left);
    vec_destroy(&right);
    vec_destroy(&out);
}

void vec_algs_get_union_basic(void) {
    vec_t a, b, out;
    vec_init(&a, 0, sizeof(int));
    vec_init(&b, 0, sizeof(int));

    int av[] = {1, 2, 3, 4, 5};
    int bv[] = {3, 4, 5, 6, 7};

    for (int i = 0; i < 5; i++) {
        vec_push_back(&a, &av[i]);
        vec_push_back(&b, &bv[i]);
    }

    ASSERT_INT_EQ("Merging standard sets together via union operations returns VEC_OK", VEC_OK, vec_get_union(&a, &b, vec_default_ordering, &out));
    ASSERT_INT_EQ("Standard distinct combined values size checks out", 7, vec_size(&out));

    int expected[] = {1, 2, 3, 4, 5, 6, 7};
    for (int i = 0; i < 7; i++) {
        int v;
        vec_get(&out, i, &v);
        ASSERT_INT_EQ("Tracking combined array data sequential positions mapping values", expected[i], v);
    }

    vec_destroy(&a);
    vec_destroy(&b);
    vec_destroy(&out);
}

void vec_algs_get_union_left_empty(void) {
    vec_t a, b, out;
    vec_init(&a, 0, sizeof(int));
    vec_init(&b, 0, sizeof(int));

    int v = 1;
    vec_push_back(&b, &v);

    ASSERT_INT_EQ("Executing empty-set union wrappers returns VEC_OK", VEC_OK, vec_get_union(&a, &b, vec_default_ordering, &out));
    ASSERT_FALSE("Union merge against a populating set cannot pass up as empty layout", vec_is_empty(&out));

    v = 0;
    vec_get(&out, 0, &v);
    ASSERT_INT_EQ("Extracted target index matches populating vector source components", 1, v);

    vec_destroy(&a);
    vec_destroy(&b);
    vec_destroy(&out);
}

void vec_algs_get_union_both_empty(void) {
    vec_t a, b, out;
    vec_init(&a, 0, sizeof(int));
    vec_init(&b, 0, sizeof(int));

    ASSERT_INT_EQ("Executing master double empty set combination sweeps returns VEC_OK", VEC_OK, vec_get_union(&a, &b, vec_default_ordering, &out));
    ASSERT_TRUE("Combined space tracking across empty arrays must evaluate to blank output", vec_is_empty(&out));

    vec_destroy(&a);
    vec_destroy(&b);
    vec_destroy(&out);
}

void vec_algs_get_union_with_duplicates(void) {
    vec_t a, b, out;
    vec_init(&a, 0, sizeof(int));
    vec_init(&b, 0, sizeof(int));

    int av[] = {1, 2, 2, 3, 3, 3};
    int bv[] = {2, 2, 3, 4};

    for (int i = 0; i < 6; i++) vec_push_back(&a, &av[i]);
    for (int i = 0; i < 4; i++) vec_push_back(&b, &bv[i]);

    ASSERT_INT_EQ("Executing union combinations over multiple repetitive layers returns VEC_OK", VEC_OK, vec_get_union(&a, &b, vec_default_ordering, &out));
    ASSERT_INT_EQ("Union output structural processing filters duplicates away to unique layout counts", 4, vec_size(&out));

    int expected[] = {1, 2, 3, 4};
    for (int i = 0; i < 4; i++) {
        int v;
        vec_get(&out, i, &v);
        ASSERT_INT_EQ("Tracking deduplicated output elements validation indices positions", expected[i], v);
    }
    
    vec_destroy(&a);
    vec_destroy(&b);
    vec_destroy(&out);
}

void vec_algs_get_union_identical(void) {
    vec_t a, b, out;
    vec_init(&a, 0, sizeof(int));
    vec_init(&b, 0, sizeof(int));

    int v[] = {1, 2, 3};

    for (int i = 0; i < 3; i++) {
        vec_push_back(&a, &v[i]);
        vec_push_back(&b, &v[i]);
    }

    ASSERT_INT_EQ("Merging perfectly matching array mirror ranges via union layers returns VEC_OK", VEC_OK, vec_get_union(&a, &b, vec_default_ordering, &out));
    ASSERT_INT_EQ("Union output size constraint boundaries over mirroring elements", 3, vec_size(&out));

    int expected[] = {1, 2, 3};
    for (int i = 0; i < 3; i++) {
        int val;
        vec_get(&out, i, &val);
        ASSERT_INT_EQ("Confirming sequential identity allocations data indices mirror layouts", expected[i], val);
    }

    vec_destroy(&a);
    vec_destroy(&b);
    vec_destroy(&out);
}

void vec_algs_get_union_null_args(void) {
    vec_t a;
    vec_init(&a, 0, sizeof(int));

    ASSERT_INT_EQ("Union invocation carrying parameter 1 NULL configuration failures", VEC_ERROR_NULL, vec_get_union(NULL, &a, vec_default_ordering, &a));
    ASSERT_INT_EQ("Union invocation carrying parameter 2 NULL configuration failures", VEC_ERROR_NULL, vec_get_union(&a, NULL, vec_default_ordering, &a));
    ASSERT_INT_EQ("Union invocation carrying parameter 3 NULL target context allocations", VEC_ERROR_NULL, vec_get_union(&a, &a, vec_default_ordering, NULL));

    vec_destroy(&a);
}

void vec_algs_get_union_unsorted_input(void) {
    vec_t a, b, out;
    vec_init(&a, 0, sizeof(int));
    vec_init(&b, 0, sizeof(int));

    int av[] = {3, 1, 2}; 
    int bv[] = {1, 2, 3};

    for (int i = 0; i < 3; i++) {
        vec_push_back(&a, &av[i]);
        vec_push_back(&b, &bv[i]);
    }

    ASSERT_INT_EQ("Processing mathematical union sets across unsorted inputs triggers structural runtime failure", VEC_ERROR_INVALID, vec_get_union(&a, &b, vec_default_ordering, &out));

    vec_destroy(&a);
    vec_destroy(&b);
}

void vec_algs_get_union_descending(void) {
    vec_t left, right, out;
    vec_init(&left, 0, sizeof(int));
    vec_init(&right, 0, sizeof(int));

    int lv[] = {9, 7, 5, 3, 1};
    int rv[] = {8, 7, 6, 5, 4};

    for (int i = 0; i < 5; i++) {
        vec_push_back(&left, &lv[i]);
        vec_push_back(&right, &rv[i]);
    }

    ASSERT_INT_EQ("Merging sets defined down descending sequential tracks returns VEC_OK", VEC_OK, vec_get_union(&left, &right, vec_default_ordering, &out));
    ASSERT_INT_EQ("Combined size total output tracking footprint under descending rules", 8, vec_size(&out));

    int expected[] = {9, 8, 7, 6, 5, 4, 3, 1};

    for (int i = 0; i < 8; i++) {
        int v;
        vec_get(&out, i, &v);
        ASSERT_INT_EQ("Verifying items mapping position layout alignment over descending combined structures", expected[i], v);
    }

    vec_destroy(&left);
    vec_destroy(&right);
    vec_destroy(&out);
}

void vec_algs_is_unique_simple(void) {
    vec_t d;
    vec_init(&d, 0, sizeof(size_t));

    for (size_t i = 0; i < 10; i++) {
        vec_push_back(&d, &i);
    }

    ASSERT_TRUE("Unique sequential series must evaluate positively under verification sweeps", vec_is_unique(d, vec_default_ordering));

    vec_destroy(&d);
}

void vec_algs_is_unique_false(void) {
    vec_t d;
    vec_init(&d, 0, sizeof(size_t));

    for (size_t i = 0; i < 10; i++) {
        vec_push_back(&d, &i);
    }
    size_t i = 9;
    vec_push_back(&d, &i);

    ASSERT_FALSE("Appending duplicate item states manually must break uniqueness status evaluations", vec_is_unique(d, vec_default_ordering));

    vec_destroy(&d);
}

void vec_algs_is_unique_empty(void) {
    vec_t d;
    vec_init(&d, 0, sizeof(size_t));

    ASSERT_TRUE("Blank array fields register as uniquely allocated collections by default", vec_is_unique(d, vec_default_ordering));

    vec_destroy(&d);
}

void vec_algs_is_unique_all_same(void) {
    vec_t d;
    vec_init(&d, 0, sizeof(int));

    int a = 10;
    for (int i = 0; i < 10; i++) {
        vec_push_back(&d, &a);
    }

    ASSERT_FALSE("Homogeneous uniform content sets must fail uniqueness verification checks", vec_is_unique(d, vec_default_ordering));

    vec_destroy(&d);
}

void vec_algs_get_unique_simple(void) {
    vec_t d;
    vec_init(&d, 0, sizeof(int));

    for (int i = 0; i < 20; i++) {
        if (i % 2 == 1)
            i++;
        vec_push_back(&d, &i);
    }

    vec_t e;
    ASSERT_INT_EQ("Deduplicating standard variable arrays into target outputs returns VEC_OK", VEC_OK, vec_get_unique(&d, vec_default_ordering, &e));
    ASSERT_TRUE("Deduplicated array output metrics verify as uniquely populated structures", vec_is_unique(e, vec_default_ordering));

    vec_destroy(&d);
    vec_destroy(&e);
}

void vec_algs_get_unique_all_same(void) {
    vec_t d;
    vec_init(&d, 0, sizeof(int));

    int a = 10;
    for (int i = 0; i < 10; i++) {
        vec_push_back(&d, &a);
    }

    vec_t e;
    ASSERT_INT_EQ("Deduplicating continuous overlapping data blocks returns VEC_OK", VEC_OK, vec_get_unique(&d, vec_default_ordering, &e));
    ASSERT_TRUE("Condensed duplicate collections are transformed down to distinct elements sets", vec_is_unique(e, vec_default_ordering));

    vec_destroy(&d);
    vec_destroy(&e);
}

void vec_algs_get_unique_already_unique(void) {
    vec_t d;
    vec_init(&d, 0, sizeof(int));

    for (int i = 0; i < 10; i++) {
        vec_push_back(&d, &i);
    }

    vec_t e;
    ASSERT_INT_EQ("Isolating records over pre-sorted clear baseline arrays returns VEC_OK", VEC_OK, vec_get_unique(&d, vec_default_ordering, &e));
    ASSERT_TRUE("Running deduplication routines across fine configurations sustains unique identity flags", vec_is_unique(e, vec_default_ordering));

    vec_destroy(&d);
    vec_destroy(&e);
}

void vec_algs_sort_empty(void) {
    vec_t d;
    vec_init(&d, 0, sizeof(int));

    ASSERT_INT_EQ("Sorting clear unallocated arrays returns VEC_OK", VEC_OK, vec_sort(&d, vec_default_ordering));
    ASSERT_TRUE("Blank collections naturally pass sorting checks afterwards", vec_is_sorted_asc(d, vec_default_ordering));

    vec_destroy(&d);
}

void vec_algs_sort_single(void) {
    vec_t d;
    vec_init(&d, 0, sizeof(int));

    int x = 42;
    vec_push_back(&d, &x);

    ASSERT_INT_EQ("Sorting micro layouts containing single elements returns VEC_OK", VEC_OK, vec_sort(&d, vec_default_ordering));
    ASSERT_TRUE("Isolated items check out perfectly as sorted parameters", vec_is_sorted_asc(d, vec_default_ordering));

    vec_destroy(&d);
}

void vec_algs_sort_already_sorted(void) {
    vec_t d;
    vec_init(&d, 0, sizeof(int));

    for (int i = 0; i < 10; i++) {
        vec_push_back(&d, &i);
    }

    ASSERT_INT_EQ("Running sort passes against pre-ordered items returns VEC_OK", VEC_OK, vec_sort(&d, vec_default_ordering));
    ASSERT_TRUE("Pre-sorted arrays must sustain chronological validity layout flags", vec_is_sorted_asc(d, vec_default_ordering));

    vec_destroy(&d);
}

void vec_algs_sort_reverse(void) {
    vec_t d;
    vec_init(&d, 0, sizeof(int));

    for (int i = 9; i >= 0; i--) {
        vec_push_back(&d, &i);
    }

    ASSERT_INT_EQ("Sorting back-to-front inverted array parameters returns VEC_OK", VEC_OK, vec_sort(&d, vec_default_ordering));
    ASSERT_TRUE("Inverted layouts are correctly transformed up to ordered states", vec_is_sorted_asc(d, vec_default_ordering));

    vec_destroy(&d);
}

void vec_algs_sort_with_duplicates(void) {
    vec_t d;
    vec_init(&d, 0, sizeof(int));

    int values[] = {3, 1, 2, 3, 2, 1, 3};
    for (size_t i = 0; i < sizeof(values) / sizeof(values[0]); i++) {
        vec_push_back(&d, &values[i]);
    }

    ASSERT_INT_EQ("Sorting records mixed with overlapping duplicate entries returns VEC_OK", VEC_OK, vec_sort(&d, vec_default_ordering));
    ASSERT_TRUE("Arrays layered with duplicates must resolve into contiguous ascending subsets", vec_is_sorted_asc(d, vec_default_ordering));

    vec_destroy(&d);
}

void vec_algs_sort_random_small(void) {
    vec_t d;
    vec_init(&d, 0, sizeof(int));

    int values[] = {4, 2, 9, 1, 5};
    for (size_t i = 0; i < sizeof(values) / sizeof(values[0]); i++) {
        vec_push_back(&d, &values[i]);
    }

    ASSERT_INT_EQ("Sorting completely scrambled random layouts returns VEC_OK", VEC_OK, vec_sort(&d, vec_default_ordering));
    ASSERT_TRUE("Scrambled configurations must unify under strict ordering validation checks", vec_is_sorted_asc(d, vec_default_ordering));

    vec_destroy(&d);
}

void vec_algs_sort_all_equal(void) {
    vec_t d;
    vec_init(&d, 0, sizeof(int));

    int x = 7;
    for (int i = 0; i < 10; i++) {
        vec_push_back(&d, &x);
    }

    ASSERT_INT_EQ("Sorting homogeneous clusters of identical variables returns VEC_OK", VEC_OK, vec_sort(&d, vec_default_ordering));
    ASSERT_TRUE("Constant structural components fulfill sorting requirements safely", vec_is_sorted_asc(d, vec_default_ordering));

    vec_destroy(&d);
}

void vec_algs_tests() {
    printf("--- RUNNING EXTENDED VECTOR TESTS ---\n");

    RUN_TEST(vec_algs_find_first_one_option);
    RUN_TEST(vec_algs_find_first_two_options);
    RUN_TEST(vec_algs_find_first_no_option);
    RUN_TEST(vec_algs_find_last_one_option);
    RUN_TEST(vec_algs_find_last_two_options);
    RUN_TEST(vec_algs_find_last_no_option);
    RUN_TEST(vec_algs_find_first_last_empty);
    RUN_TEST(vec_algs_binary_search_simple);
    RUN_TEST(vec_algs_binary_search_empty);
    RUN_TEST(vec_algs_binary_search_small);
    RUN_TEST(vec_algs_is_sorted_asc_simple);
    RUN_TEST(vec_algs_is_sorted_empty);
    RUN_TEST(vec_algs_is_sorted_asc_all_same);
    RUN_TEST(vec_algs_is_sorted_asc_false);
    RUN_TEST(vec_algs_is_sorted_desc_simple);
    RUN_TEST(vec_algs_is_sorted_desc_all_same);
    RUN_TEST(vec_algs_is_sorted_desc_false);
    RUN_TEST(vec_algs_reverse_basic);
    RUN_TEST(vec_algs_range_simple_forward);
    RUN_TEST(vec_algs_range_forward_step_two);
    RUN_TEST(vec_algs_range_backward);
    RUN_TEST(vec_algs_range_backward_step_two);
    RUN_TEST(vec_algs_range_empty);
    RUN_TEST(vec_algs_range_zero_step);
    RUN_TEST(vec_algs_range_invalid_negative_step_forward);
    RUN_TEST(vec_algs_range_invalid_positive_step_backward);
    RUN_TEST(vec_algs_range_stop_exclusive);
    RUN_TEST(vec_algs_range_null_self);
    RUN_TEST(vec_algs_get_intersection_basic);
    RUN_TEST(vec_algs_get_intersection_none);
    RUN_TEST(vec_algs_get_intersection_left_empty);
    RUN_TEST(vec_algs_get_intersection_both_empty);
    RUN_TEST(vec_algs_get_intersection_with_duplicates);
    RUN_TEST(vec_algs_get_intersection_identical);
    RUN_TEST(vec_algs_get_intersection_null_args);
    RUN_TEST(vec_algs_get_intersection_unsorted_input);
    RUN_TEST(vec_algs_get_intersection_descending);
    RUN_TEST(vec_algs_get_union_basic);
    RUN_TEST(vec_algs_get_union_left_empty);
    RUN_TEST(vec_algs_get_union_both_empty);
    RUN_TEST(vec_algs_get_union_with_duplicates);
    RUN_TEST(vec_algs_get_union_identical);
    RUN_TEST(vec_algs_get_union_null_args);
    RUN_TEST(vec_algs_get_union_unsorted_input);
    RUN_TEST(vec_algs_get_union_descending);
    RUN_TEST(vec_algs_is_unique_simple);
    RUN_TEST(vec_algs_is_unique_false);
    RUN_TEST(vec_algs_is_unique_empty);
    RUN_TEST(vec_algs_is_unique_all_same);
    RUN_TEST(vec_algs_get_unique_simple);
    RUN_TEST(vec_algs_get_unique_all_same);
    RUN_TEST(vec_algs_get_unique_already_unique);
    RUN_TEST(vec_algs_sort_empty);
    RUN_TEST(vec_algs_sort_single);
    RUN_TEST(vec_algs_sort_already_sorted);
    RUN_TEST(vec_algs_sort_reverse);
    RUN_TEST(vec_algs_sort_with_duplicates);
    RUN_TEST(vec_algs_sort_random_small);
    RUN_TEST(vec_algs_sort_all_equal);

    printf("\n");
}
