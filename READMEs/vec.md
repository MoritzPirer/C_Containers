# VEC

vec is a library written in C17 that provides an automatically resizing array. It provides many of the functionalities that C++'s vector provides. All core vec functions are declared in `vec.h`.

The accompanying header file `vec_algs.h` provides some useful algorithms for common operations such as searching, sorting or iterating.

This Readme provides some usage notes. The more detailed information is in the header files.

## GENERAL
Most functions return a `vec_status_t` enum value. Possible return values are:
- `VEC_OK`: the operation succeded
- `VEC_ERROR_ALLOCATION`: a malloc or realloc call failed
- `VEC_ERROR_NULL`: at least one argument was NULL when it shouldn't have been
- `VEC_ERROR_BOUNDS`: A given index was out of range of the vec
- `VEC_ERROR_INVALID`: An input was given in a way that the library cannot accept
- `VEC_NOT_FOUND`: (used by find operations in `vec_algs`) no matching element was found

The struct members should not be accessed directly. Always use the apropriate function call.

The vec does not provide thread safety. It is up to you to lock accesses where apropriate.

## OWNERSHIP
Create a new vec object using `vec_t variable_name`. Do not initialize it manually. Instead, use `vec_init(vec_t* self, size_t initial_size, size_t element_size)` this sets up the vec to have `initial_size` elements of size `element_size` (It is recommended you use `sizeof(DATA_TYPE)` as `element_size`). Note that setting the `initial_size` parameter to a value > 0 means that the vec will be initialized with that number of zeroed elements. This is mainly intended to avoid repeated reallocation if the vector is immediately populated with `vec_set`. Some functions in `vec_algs` require an uninitialized `vec_t` and initialize it for you.
Unless specifically requested, it is undefined behavior to pass an uninitialized `vec_t` to a function.

You can release the `vec_t`'s resources using `vec_destroy(vec_t*)`. calling this on the same `vec_t` multiple times is harmless. Passing a `vec_t` to a function after it has been destroyed is equivalent to passing an uninitialized one (i.e. okay only when explicitly expected).

Copying the `vec_t` struct creates a shallow copy, i.e. the elements are shared. Be careful with this as it could result in stale metadata causing undefined behavior. You can create a deep copy (i.e. same values, but seperate memory) usind `vec_copy()`.

## SIZE & CAPACITY
Size always refers to the number of elements in use. Capacity alway refers to the number of elements already allocated for.
If the vec is full, it will automatically double its size upon the next operation that adds an element. If an operation causes it to be less than half full, it will shrink to half the size (note that bulk deletion, i.e. with `vec_erase_all()` will still only halve the capacity so erasing from a 16 element vec will shrink it to capacity 8, even though it has 0 elements.)
You can use `vec_reserve()` to guarantee a minimum for capacity.

## STRUCTURE
You can add and remove elements to / from the front and the back. For `vec_push_back()` and `vec_push_front()`, you need the value you want to store in a local variable, and pass a pointer to that variable. `vec_insert()` works similarly.
Similarly, for `vec_pop_back()` and `vec_pop_front()`, you need to provide a pointer as the destination.

## ERASING
`vec_erase_from_to()` erases within the given indecies (including both indices themselves). The other functions of the erase family are aliases that fix the start and / or the end of the erase:
- `vec_erase_from(start)` is equivalent to `vec_erase_from_to(start, [LAST ELEMENT'S INDEX]`)
- `vec_erase_to(end)` is equivalent to `vec_erase_from_to(0, end)`
- `vec_erase_all()` and `vec_clear()` are equivalent to `vec_erase_from_to(0, [LAST ELEMENT'S INDEX]`)
- `vec_erase_at(index)`is equivalent to `vec_erase_from_to(index, index)`

## ACCESS
These allow you to read or write single elements of the darray. Like the push and pop methods, you need to provide a variable buffer to read to / write from.

`vec_data()` allows you to get a direct pointer to the elements. This should be done carefully as any operation that adds or removes elements has a chance to reallocate the data, making the pointer invalid


## SEARCHING
`find_first` example usage:

```c
bool condition(const void* element, const void* data) {
    return (*(size_t*) element == *(size_t*) data);
}

size_t target = 2;
DarrayStatus res = darrayFindFirst(&d, condition, &temp, &target);
if (res == VEC_OK) {
    //do something with index of value 2
}

size_t target = 3;
DarrayStatus res = darrayFindFirst(&d, condition, &temp, &target);
if (res == VEC_OK) {
    //do something with index of value 3
}
```

`vec_binary_search()` assumes unique values and ascending sorting. This is not verified, as doing so would defeat the purpose of using binary search in the first place by degrading the runtime from O(log(n)) to O(n).

## SETLIKE OPERATONS
These functions require sorted darrays to maintain linear runtimes.



# VEC
vec is a library written in C17 that provides a dynamically resizing array. It provides many methods that C++'s `std::vector<T>` provides. All core functions are provided in `vec.h`. The header file `vec_algs.h` declares some commonly used function for searching, content testing, etc.
This Readme provides some usage notes in addition to the information provided in the comments of the header files.

## GENERAL
Most functions return a `vec_status_t` enum value. Possible return values are:
- `VEC_OK`: the operation succeded
- `VEC_ERROR_ALLOCATION`: a creating a new vec or resizing an existing one failed. Note that resizing may happen implicitly whenever items are added or removed from the vec.
- `VEC_ERROR_BOUNDS`: A given index was out of range of the vec
- `VEC_ERROR_NULL`: A pointer passed to the function was NULL when it shouldn't have been
- `VEC_ERROR_INVALID`: A parameter had a logically invalid value
- `VEC_NOT_FOUND`: (used by find operations in `vec_algs`) no matching element was found

The members of the `vec_t` struct should never be accessed directly, rather always use an appropriate function call
The operations do not provide thread safety. It is up to you to lock accesses where appropriate.

## OWNERSHIP
Create a new vec with `vec_t variable_name`. Initialize with `vec_init`, never by hand.
- `initial_capacity` specifies with what capacity the vec is created. When known, this can be set to the number of elements the set will contain to reduce reallocation. 
- `element_size` should always be set with `sizeof(TYPE)`, it defines how large each element is.

Release the vec's resources with `vec_destroy`. This is save to call multiple times on the same vec

Some functions explicitly expect an uninitialized vec, all others expect it to be initialized already. A vec on which `vec_destroy` has been called alreadyy can be used as if it were uninitialized. Passing an uninitialized vec where an initialized one is expected is undefined behavior, passing an initialized one where an uninitialized one is expected will leak memory.

```c
vec_t vec;
if (vec_init(&vec, 4, sizeof(int)) != VEC_OK) {
	//handle failure
}

// vec is now usable

vec_destroy(&vec);
```

Create a deep copy of a vec with `vec_copy`. (Shallow-)copying the struct itself is not recommended as metadata (including the data itself) can become outdated. Copying a pointer to a `vec_t` is generally safe.

Swap two vecs with `vec_swap`.

## SIZE & CAPACITY

- `vec_reserve` increases the capacity of the vec to at least the specified amount, such that it can hold at least that many elements before having to resize again
- `vec_resize` increases or decreases the size of the vec to exactly the specified amount. Sizing up sets new elements to 0. Sizing down loses elements that don't fit anymore
- `vec_shrink` shrinks the capacity to match the size
- `vec_size` and `vec_capacity` return the current size and capacity respectively
- `vec_is_empty` returns true if the current size is zero

## STRUCTURE

All functions in this section receive a pointer to a buffer location from which they read or to which they write.
- `vec_push_back` adds the element to the end of the vec
- `vec_pop_back` removes the last element of the vec (fails if the vec is empty)
- `vec_push_front` adds the element to the start of the vec
- `vec_pop_front` removes the first element of the vec (fails if the vec is empty)
- `vec_insert` inserts the element at the specified index

## ERASING
The fundamental function for erasing is `vec_erase_from_to` which expects a start and end index between which to delete (including both end points). The following functions default one or both of the indices:
- `vec_erase_from` deletes from the index to the end of the vec (inclusive)
- `vec_erase_to` deletes from the start to that index (inclusive)
- `vec_erase_at` deletes the specified index
- `vec_erase_all` and `vec_clear` erase the entire vec

## ACCESS
Similar to the structure functions, these `vec_get` and `vec_set` use a buffer to read / write the element
`vec_data` returns a raw pointer to the data. This pointer should not be used after any adding / removing actions.

## INTEGRATION
This section covers integration with other containers in the library.

`vec_to_hset` creates an hset that contains all (unique) values of the vec.

## ITERATOR
The header `vec_iter.h` provides an iterator. Initalize it with `vec_iter_init`. The iterator does not need to be destroyed (i.e. there is no `vec_iter_destroy`). The iterator is invalidated by any methods in `vec.h` and `vec_algs.g` that...
- change the size
- change the capacity
- change the order of elements
... of the vector being iterated. If that happens, the iterator functions will return `VEC_ITER_INVALID`. Specifically, all of these functions will invalidate the iterator:
- `vec_erase_from_to`, `vec_erase_from`, `vec_erase_to`, `vec_erase_at`, `vec_erase_all`, `vec_clear`
- `vec_swap` (both are invalidated) `vec_append` (only the one being appended to, not the one being appended)
- `vec_reserve`, `vec_shrink`, `vec_resize`
- `vec_push_back`, `vec_pop_back`, `vec_push_front`, `vec_pop_front`, `vec_insert`
- `vec_reverse`, `vec_sort`

If the iterator is on one of the ends, and would be moved out of bounds by the method, it will not move and return `VEC_ITER_END` instead.

Read from / write to the current position of the iterator with `vec_iter_get` and `vec_iter_set` respectively. Use `vec_iter_has_next` and `vec_iter_has_previous` to check if the iterator can move in that direction.

move the iterator with `vec_iter_next` and `vec_iter_next` these take a `void*` to write the element the iterator *lands on* to. If that element is not needed, you can savely pass NULL to disregard.
