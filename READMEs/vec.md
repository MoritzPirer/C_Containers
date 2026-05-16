# VEC

vec is a library written in C17 that provides an automatically resizing array. It provides many of the functionalities that C++'s vector provides. All core vec functions are declared in `inc/vec.h.

The accompanying header file `inc/vec_algs.h` provides some useful algorithms for common operations such as searching, sorting or iterating.

This Readme provides some usage notes. The more detailed information is in the header files.

## GENERAL
Most functions return a vec_status_t enum value. Possible return values are:
- VEC_OK: the operation succeded
- VEC_ERROR_ALLOCATION: a malloc or realloc call failed
- VEC_ERROR_NULL: at least one argument was NULL when it shouldn't have been
- VEC_ERROR_BOUNDS: A given index was out of range of the vec
- VEC_ERROR_INVALID: An input was given in a way that the library cannot accept
- VEC_NOT_FOUND: (used by find operations in vec_algs) no matching element was found

The struct members should not be accessed directly. Always use the apropriate function call.

The vec does not provide thread safety. It is up to you to lock accesses where apropriate.

## MEMORY
Create a new vec object using `vec_t variable_name`. Do not initialize it manually. Instead, use `vec_init(vec_t* self, size_t initial_size, size_t element_size)` this sets up the vec to have initial_size elements of size element_size (It is recommended you use sizeof(DATA_TYPE) as element_size). Some functions in vec_algs require an uninitialized vec_t and initialize it for you.
Unless specifically requested, it is undefined behavior to pass an uninitialized vec_t to a function.

You can release the vec_t's resources using `vec_destroy(Darry*)`. calling this on the same vec_t multiple times is harmless. Passing a vec_t to a function after it has been destroyed is equivalent to passing an uninitialized one (i.e. okay only when explicitly expected).

Copying the vec_t struct creates a shallow copy, i.e. the elements are shared. Be careful with this as it could result in stale metadata causing undefined behavior. You can create a deep copy (i.e. same values, but seperate memory) usind `vec_copy()`.

## SIZE & CAPACITY
Size always refers to the number of elements in use. Capacity alway refers to the number of elements already allocated for.
If the vec is full, it will automatically double its size upon the next operation that adds an element. If an operation causes it to be less than half full, it will shrink to half the size (note that bulk deletion, i.e. with `vec_erase_all()` will still only halve the capacity so erasing from a 16 element vec will shrink it to capacity 8, even though it has 0 elements.)
You can use `vec_reserve()` to guarantee a minimum for capacity.

## STRUCTURE
You can add and remove elements to / from the front and the back. For `vec_push_back()` and `vec_push_front()`, you need the value you want to store in a local variable, and pass a pointer to that variable. `vec_insert()` works similarly.
Similarly, for `vec_pop_back()` and `vec_pop_front()`, you need to provide a pointer as the destination.

## ERASING
`vec_erase_from_to()` erases within the given indecies (including both indices themselves). The other functions of the erase family are aliases that fix the start and / or the end of the erase:
- `vec_erase_from(start)` is equivalent to `vec_erase_from_to(start, [LAST ELEMENT'S INDEX])
- `vec_erase_to(end)` is equivalent to `vec_erase_from_to(0, end)
- `vec_erase_all()` and `vec_clear()` are equivalent to `vec_erase_from_to(0, [LAST ELEMENT'S INDEX])
- `vec_erase_at(index)`is equivalent to `vec_erase_from_to(index, index)`

## ACCESS
These allow you to read or write single elements of the darray. Like the push and pop methods, you need to provide a variable buffer to read to / write from.

`vec_data()` allows you to get a direct pointer to the elements. This should be done carefully as any operation that adds or removes elements has a chance to reallocate the data, making the pointer invalid


## SEARCHING
find_first example usage:

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
