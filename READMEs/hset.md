# HSET
hset is a library written in C17 that provides a set implemented as a hash table. All functions are declared in `hset.h`. This Readme provides some usage notes in addition to the information provided in the comments of the header file.

## GENERAL
Many functions return an `hset_status_t` enum value indicating the result of the operation. Possible values are:
- `HSET_OK`: the operation succeeded
- `HSET_ERROR_ALLOCATION`: Creating a new hset or resizing an existing one failed. Note that resizing may happen implicitly whenever items are added or removed from the set.
- `HSET_ERROR_NULL`: A pointer passed to the function was NULL when it should not have been
- `HSET_ERROR_INVALID`: A parameter had a logically invalid value

The members of the `hset_t` struct should never be accessed directly, rather always use an appropriate function call.
The operations do not provide thread safety. It is up to you to lock accesses where appropriate.

## OWNERSHIP
Create a new set with `hset_t variable_name`. Initialize with `hset_init`, never by hand.
- `initial_capacity` specifes with what capacity the hset is created. When known, this can be set to the number of elements the set will contain to reduce reallocations. Note that resizing happens before the hset is completely full for efficiency reasons. If the number of items is not known in advance, set it to 0
- `element_size` should always be set with `sizeof(TYPE)`, it defines how large each element is.
- `comparison` is a function that determines when two elements are equal. If NULL is passed, the default is comparing the bits of the entries. when in doubt, use your own function.

Release the hset's resources with `hset_destroy`. This is safe to call multiple times on the same hset.

Some functions explicitly expect an uninitialized hset, all others expect it to be initialized already. An hset on which `hset_destroy` has been called already can be used as if it were uninitialized. Passing an uninitialized hset where an inizialized one is expected is undefined behavior, passing an initialized one where an uninitalized one is expected will leak memory.

```c
hset_t hset;
if (hset_init(&hset, 4, sizeof(size_t), NULL) != HSET_OK) {
	// handle failure
}

// hset is now usable

hset_destroy(&hset);
```

Create a deep copy of an hset with `hset_copy`. (Shallow-)copying the struct itself is not recommended as metadata (including the data itself) can become outdated. Copying a pointer to an `hset_t` is generally safe.

## CORE FUNCTIONS
Add items with `hset_add`. The `source` parameter must point to a place in memory that is at least as big as the element size defined at initalization. In concurrent contexts, it must be ensured that the memory remains valid and unchanged until the function call returns. Adding an item that is already contained has no effect (i.e. the element is still only contained once).

Remove items with `hset_remove`. The `source` parameter has the same requirements as in `hset_add`. Trying to remove an element that is not contained (or removing one element twice) is harmless and returns `HSET_OK`

Test membership with `hset_contains`. Like `source` in the previous cases, the `item` parameter must remain valid and unchanged for the duration of this function. Passing NULL as one of the pointers returns false.

`hset_size` returns the number of elements in the hset, `hset_is_empty` returns true if no elements are contained. `hset_clear` clears all elements, but does **not** reset the allocated capacity.

`hset_equals` compares two hsets for equality. hsets are considered equal if they have the same comparison function and item size, and if the symmetric difference is an empty set.

## (MATHEMATICAL) SET OPERATIONS
The following functions take three `hset_t`s. The first two must be initialized, the third one must be uninitialized. It will be initialized for you and populated with the result of the operation. It is also required that the first `hset_t`s have the same item size and comparison function.

`hset_union(const hset_t* a, const hset_t* b, hset_t* result)` initializes result to contain all elemets in *one or both* of the hsets.
`hset_intersection(const hset_t* a, const hset_t* b, hset_t* result)` initalizes result to contain all elements in *both* of the hsets.
`hset_difference(const hset_t* a, const hset_t* b, hset_t* result)` initalizes result to contain all elements that are *in a, but not in b*.
`hset_symmetric_difference(const hset_t* a, const hset_t* b, hset_t* result)` initializes result to contain all elements that are in *one of the hsets, but not both*.


The last two functions of this section only expect two (initalized) `hset_t`s.

`hset_is_subset_of(const hset_t* a, const hset_t* b)` returns true if all elements of `a` are also contained in `b`
`hset_is_superset_of(const hset_t* a, const hset_t* b)` returns true if all elements of `b` are also contained in `a`.

## CONTENT TESTING
This section uses `hset_condition_t`. It takes an element in the the hset (passed as a `const void*`) and returns a boolean value. It also takes a second `const void*` that can be used to pass extra data to the comparison (see the example below).

`hset_filter(hset_t* self, hset_condition_t condition, hset_t* filtered, const void* data)` initalizes `filtered` to contain all elements for which `condition` returns true.

`hset_all(hset_t* self, hset_condition_t condition, const void* data)` returns true if the condition is true for all elements.
`hset_any(hset_t* self, hset_condition_t condition, const void* data)` returns true if the condition is true for at least one element.
`hset_none(hset_t* self, hset_condition_t condition, const void* data)` returns true if the condition is false for all elements.

```c
bool less_than(const void* element, const void* data) {
	return (*(size_t* )element < *(size_t* )data);
}


// assume that a is initialized hsets with values 1 - 10 (size_t)

size_t data = 10;
if (hset_any(&a, less_than, &data) {
	// this path is taken because at least one element in a is less than 10
}

data = 4;
if (hset_all(&a, less_than, &data) {
	// this path is NOT taken because at least one element is not less than 4
}

data = 3;
hset_t b;
hset_filter(&a, less_than, &b, &data);

// b is now initialized and contains the values {1, 2}; a is unchanged

```

## INTEGRATION
This section covers functions that interact with other containers of this library.

`hset_to_vec` initializes a vec to contain all elements of the hset (in whatever order they happened to be in in internal storage)

`hset_add_all` adds all elements contained in the vec to the hset
`hset_remove_all` removes all elements contained in the vec from the hset
`hset_contains_all` returns true if all elements of the vec are contained in the set
`hset_contains_any` returns true if at least one element of the vec is contained in the set

