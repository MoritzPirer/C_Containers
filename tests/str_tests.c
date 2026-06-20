#include "../inc/str/str.h"
#include "tests.h"
#include <string.h>
#include <stdbool.h>

void str_init_test() {
    str_t str;

    ASSERT_TRUE("init should fail if self is NULL", str_init(NULL, 10) == STR_ERROR_NULL);
    ASSERT_TRUE("capacity 0 should be allowed", str_init(&str, 0) == STR_OK);
    ASSERT_TRUE("capacity 0 should default up", str.capacity >= STR_MIN_CAPACITY);
    ASSERT_TRUE("Size should be 0", str_size(&str) == 0);
    
    str_destroy(&str);
}

void str_init_repeat_test() {
    str_t str;

    ASSERT_TRUE("init repeat should fail if self is NULL", str_init_repeat(NULL, 'c', 10) == STR_ERROR_NULL);
    
    ASSERT_TRUE("count 0 should be OK", str_init_repeat(&str, 'c', 0) == STR_OK);
    ASSERT_TRUE("count 0 size should be 0", str_size(&str) == 0);
    str_destroy(&str);

    // basic case
    ASSERT_TRUE("basic repeat initialization", str_init_repeat(&str, 'a', 5) == STR_OK);
    ASSERT_TRUE("size should match count", str_size(&str) == 5);
    char c;
    ASSERT_TRUE("verify character matches", str_get_at(&str, 2, &c) == STR_OK && c == 'a');
    str_destroy(&str);

    // handles special characters
    ASSERT_TRUE("special character repetition", str_init_repeat(&str, '\n', 3) == STR_OK);
    ASSERT_TRUE("verify special char matches", str_get_at(&str, 0, &c) == STR_OK && c == '\n');
    str_destroy(&str);
}

void str_destroy_test() {
    str_t str;
    
    ASSERT_TRUE("destroy should handle NULL", str_destroy(NULL) == STR_ERROR_NULL);

    str_init(&str, 10);
    ASSERT_TRUE("normal destruction should succeed", str_destroy(&str) == STR_OK);

    ASSERT_TRUE("double destruction should handle gracefully or succeed", str_destroy(&str) == STR_OK || str_destroy(&str) == STR_ERROR_NULL);
}

void str_copy_test() {
    str_t original;
    str_t copy;

    str_init(&original, 5);
    ASSERT_TRUE("copy should fail if original is NULL", str_copy(NULL, &copy) == STR_ERROR_NULL);
    ASSERT_TRUE("copy should fail if copy target is NULL", str_copy(&original, NULL) == STR_ERROR_NULL);

    ASSERT_TRUE("copy empty string should succeed", str_copy(&original, &copy) == STR_OK);
    ASSERT_TRUE("copied string should be empty", str_size(&copy) == 0);
    str_destroy(&copy);
    str_destroy(&original);

    str_init_repeat(&original, 'x', 5);
    ASSERT_TRUE("copy populated string should succeed", str_copy(&original, &copy) == STR_OK);
    
    str_set_at(&copy, 0, 'z');
    char c_orig, c_copy;
    str_get_at(&original, 0, &c_orig);
    str_get_at(&copy, 0, &c_copy);
    ASSERT_TRUE("original remains unaffected by copy modifications", c_orig == 'x' && c_copy == 'z');

    str_destroy(&original);
    str_destroy(&copy);
}

void str_swap_test() {
    str_t a;
    str_t b;
    str_init_repeat(&a, 'a', 3);
    str_init_repeat(&b, 'b', 5);

    ASSERT_TRUE("swap should fail if self is NULL", str_swap(NULL, &b) == STR_ERROR_NULL);
    ASSERT_TRUE("swap should fail if other is NULL", str_swap(&a, NULL) == STR_ERROR_NULL);

    ASSERT_TRUE("self swap should succeed", str_swap(&a, &a) == STR_OK);
    ASSERT_TRUE("self swap shouldn't change size", str_size(&a) == 3);

    ASSERT_TRUE("basic swap should succeed", str_swap(&a, &b) == STR_OK);
    ASSERT_TRUE("a size should now be 5", str_size(&a) == 5);
    ASSERT_TRUE("b size should now be 3", str_size(&b) == 3);

    str_destroy(&a);
    str_destroy(&b);
}

void str_size_test() {
    str_t str;

    ASSERT_TRUE("size of NULL should be (size_t)-1", str_size(NULL) == (size_t)-1);

    str_init(&str, 10);
    ASSERT_TRUE("size of empty string should be 0", str_size(&str) == 0);

    str_append_char(&str, 'k');
    ASSERT_TRUE("size of non-empty string should reflect count", str_size(&str) == 1);

    str_destroy(&str);
}

void str_capacity_test() {
    str_t str;

    ASSERT_TRUE("capacity of NULL should be (size_t)-1", str_capacity(NULL) == (size_t)-1);

    str_init(&str, 0);
    ASSERT_TRUE("capacity should be at least 0 or default value", str_capacity(&str) >= 0);

    str_destroy(&str);
}

void str_is_empty_test() {
    str_t str;

    ASSERT_TRUE("NULL string should return true for empty", str_is_empty(NULL) == true);

    str_init(&str, 5);
    ASSERT_TRUE("newly initialized string should be empty", str_is_empty(&str) == true);

    str_append_char(&str, 'a');
    ASSERT_TRUE("string with char should not be empty", str_is_empty(&str) == false);

    str_destroy(&str);
}

void str_get_at_test() {
    str_t str;
    char dest;

    ASSERT_TRUE("get_at should fail if self is NULL", str_get_at(NULL, 0, &dest) == STR_ERROR_NULL);
    str_init(&str, 5);
    ASSERT_TRUE("get_at should fail if destination is NULL", str_get_at(&str, 0, NULL) == STR_ERROR_NULL);

    ASSERT_TRUE("get_at index 0 on empty string is OOB", str_get_at(&str, 0, &dest) == STR_ERROR_BOUNDS);

    str_append_char(&str, 'a'); // index 0
    str_append_char(&str, 'b'); // index 1

    ASSERT_TRUE("clearly out of bounds index", str_get_at(&str, 100, &dest) == STR_ERROR_BOUNDS);
    ASSERT_TRUE("barely out of bounds (index == size)", str_get_at(&str, 2, &dest) == STR_ERROR_BOUNDS);
    ASSERT_TRUE("negative index underflow test", str_get_at(&str, (size_t)-1, &dest) == STR_ERROR_BOUNDS);
    ASSERT_TRUE("barely in bounds (index == size - 1)", str_get_at(&str, 1, &dest) == STR_OK);
    ASSERT_TRUE("retrieved value matches expectation", dest == 'b');

    str_destroy(&str);
}

void str_set_at_test() {
    str_t str;

    ASSERT_TRUE("set_at should fail if self is NULL", str_set_at(NULL, 0, 'z') == STR_ERROR_NULL);

    str_init(&str, 5);
    ASSERT_TRUE("set_at index 0 on empty string is OOB", str_set_at(&str, 0, 'z') == STR_ERROR_BOUNDS);

    str_append_char(&str, 'a');
    str_append_char(&str, 'b');

    ASSERT_TRUE("clearly out of bounds index", str_set_at(&str, 50, 'z') == STR_ERROR_BOUNDS);
    ASSERT_TRUE("barely out of bounds (index == size)", str_set_at(&str, 2, 'z') == STR_ERROR_BOUNDS);
    ASSERT_TRUE("negative index underflow test", str_set_at(&str, (size_t)-1, 'z') == STR_ERROR_BOUNDS);
    ASSERT_TRUE("barely in bounds adjustment", str_set_at(&str, 1, 'z') == STR_OK);

    char check;
    str_get_at(&str, 1, &check);
    ASSERT_TRUE("verify change stuck", check == 'z');

    str_destroy(&str);
}

void str_append_char_test() {
    str_t str;

    ASSERT_TRUE("append char fails if self is NULL", str_append_char(NULL, 'a') == STR_ERROR_NULL);

    str_init(&str, 1);
    ASSERT_TRUE("normal append char succeeds", str_append_char(&str, 'x') == STR_OK);
    ASSERT_TRUE("size increments", str_size(&str) == 1);
    ASSERT_TRUE("append forcing reallocation", str_append_char(&str, 'y') == STR_OK);
    ASSERT_TRUE("size matches after growth", str_size(&str) == 2);

    str_destroy(&str);
}

void str_append_str_test() {
    str_t self_str;
    str_t other_str;

    str_init(&self_str, 5);
    str_init(&other_str, 5);

    ASSERT_TRUE("append str fails if self is NULL", str_append_str(NULL, &other_str) == STR_ERROR_NULL);
    ASSERT_TRUE("append str fails if other is NULL", str_append_str(&self_str, NULL) == STR_ERROR_NULL);
    ASSERT_TRUE("appending an empty string succeeds", str_append_str(&self_str, &other_str) == STR_OK);
    ASSERT_TRUE("size remains 0", str_size(&self_str) == 0);
    str_append_char(&other_str, 'a');
    ASSERT_TRUE("appending populated string to empty succeeds", str_append_str(&self_str, &other_str) == STR_OK);
    ASSERT_TRUE("size updates to source string size", str_size(&self_str) == 1);

    str_t filled_src;
    str_init_repeat(&filled_src, 'b', 10); // Ensure size forces potential reallocation
    ASSERT_TRUE("append filled to filled string", str_append_str(&self_str, &filled_src) == STR_OK);
    ASSERT_TRUE("size is sum of both strings", str_size(&self_str) == 11);

    ASSERT_TRUE("self appending string", str_append_str(&self_str, &self_str) == STR_OK);
    ASSERT_TRUE("size doubles after self append", str_size(&self_str) == 22);

    str_destroy(&self_str);
    str_destroy(&other_str);
    str_destroy(&filled_src);
}

void str_prepend_char_test() {
    str_t str;

    ASSERT_TRUE("prepend char fails if self is NULL", str_prepend_char(NULL, 'a') == STR_ERROR_NULL);

    str_init(&str, 1);
    ASSERT_TRUE("normal prepend char succeeds", str_prepend_char(&str, 'b') == STR_OK);
    ASSERT_TRUE("prepend forcing reallocation", str_prepend_char(&str, 'a') == STR_OK);
    
    char check;
    str_get_at(&str, 0, &check);
    ASSERT_TRUE("prepended element is at the start", check == 'a');

    str_destroy(&str);
}

void str_prepend_str_test() {
    str_t self_str;
    str_t other_str;

    str_init(&self_str, 5);
    str_init(&other_str, 5);

    ASSERT_TRUE("prepend str fails if self is NULL", str_prepend_str(NULL, &other_str) == STR_ERROR_NULL);
    ASSERT_TRUE("prepend str fails if other is NULL", str_prepend_str(&self_str, NULL) == STR_ERROR_NULL);
    ASSERT_TRUE("prepended empty string succeeds", str_prepend_str(&self_str, &other_str) == STR_OK);

    str_append_char(&other_str, 'x');
    ASSERT_TRUE("prepend filled to empty string", str_prepend_str(&self_str, &other_str) == STR_OK);

    str_t filled_src;
    str_init_repeat(&filled_src, 'z', 15);
    ASSERT_TRUE("prepend filled to filled string", str_prepend_str(&self_str, &filled_src) == STR_OK);
    
    char check;
    str_get_at(&self_str, 0, &check);
    ASSERT_TRUE("correct structural sequence check", check == 'z');

    ASSERT_TRUE("self prepending string", str_prepend_str(&self_str, &self_str) == STR_OK);

    str_destroy(&self_str);
    str_destroy(&other_str);
    str_destroy(&filled_src);
}

void str_insert_char_test() {
    str_t str;

    ASSERT_TRUE("insert char fails if self is NULL", str_insert_char(NULL, 0, 'a') == STR_ERROR_NULL);

    str_init(&str, 5);
    ASSERT_TRUE("insert char into empty string at index 0", str_insert_char(&str, 0, 'a') == STR_OK);

    ASSERT_TRUE("insert char mid-string", str_insert_char(&str, 1, 'b') == STR_OK); 

    // str is 'ab'
    
    char check;
    str_get_at(&str, 1, &check);
    ASSERT_TRUE("verify normal insertion location", check == 'b');

    ASSERT_TRUE("barely in bounds insert (at size index)", str_insert_char(&str, 2, 'c') == STR_OK); 
    ASSERT_TRUE("barely out of bounds insert (size + 1)", str_insert_char(&str, 5, 'd') == STR_ERROR_BOUNDS);
    ASSERT_TRUE("clearly out of bounds insert", str_insert_char(&str, 200, 'f') == STR_ERROR_BOUNDS);
    ASSERT_TRUE("negative index insert underflow test", str_insert_char(&str, (size_t)-1, 'g') == STR_ERROR_BOUNDS);

    str_destroy(&str);
}

void str_insert_str_test() {
    str_t self_str;
    str_t other_str;

    str_init(&self_str, 5);
    str_init(&other_str, 5);

    ASSERT_TRUE("insert str fails if self is NULL", str_insert_str(NULL, 0, &other_str) == STR_ERROR_NULL);
    ASSERT_TRUE("insert str fails if other is NULL", str_insert_str(&self_str, 0, NULL) == STR_ERROR_NULL);

    ASSERT_TRUE("insert empty string works", str_insert_str(&self_str, 0, &other_str) == STR_OK);

    str_append_char(&other_str, 'x');
    ASSERT_TRUE("insert into empty string works", str_insert_str(&self_str, 0, &other_str) == STR_OK);

    str_t payload;
    str_init_repeat(&payload, 'y', 2);
    str_append_char(&self_str, 'z'); // self is now "xz"
    ASSERT_TRUE("normal string insertion inside text", str_insert_str(&self_str, 1, &payload) == STR_OK); // should be "xyyz"

    ASSERT_TRUE("self insertion works seamlessly", str_insert_str(&self_str, 2, &self_str) == STR_OK);

    size_t current_size = str_size(&self_str);
    ASSERT_TRUE("barely in bounds string insert", str_insert_str(&self_str, current_size, &payload) == STR_OK);
    ASSERT_TRUE("barely out of bounds string insert", str_insert_str(&self_str, str_size(&self_str) + 1, &payload) == STR_ERROR_BOUNDS);
    ASSERT_TRUE("clearly out of bounds string insert", str_insert_str(&self_str, 999, &payload) == STR_ERROR_BOUNDS);
    ASSERT_TRUE("negative index string insert test", str_insert_str(&self_str, (size_t)-1, &payload) == STR_ERROR_BOUNDS);

    str_destroy(&self_str);
    str_destroy(&other_str);
    str_destroy(&payload);
}

void str_tests() {
    printf("--- RUNNING CORE STRING TESTS ---\n");

    RUN_TEST(str_init_test);
    RUN_TEST(str_init_repeat_test);
    RUN_TEST(str_destroy_test);
    RUN_TEST(str_copy_test);
    RUN_TEST(str_swap_test);
    RUN_TEST(str_size_test);
    RUN_TEST(str_capacity_test);
    RUN_TEST(str_is_empty_test);
    RUN_TEST(str_get_at_test);
    RUN_TEST(str_set_at_test);
    RUN_TEST(str_append_char_test);
    RUN_TEST(str_append_str_test);
    RUN_TEST(str_prepend_char_test);
    RUN_TEST(str_prepend_str_test);
    RUN_TEST(str_insert_char_test);
    RUN_TEST(str_insert_str_test);

    printf("\n");
}
