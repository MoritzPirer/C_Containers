# DARRAY

Darray, short for Dynamic Array, is a library written in C17 that provides an automatically resizing array. It provides many of the functionalities that C++'s vector provides. All core darray functions are declared in `inc/darray.h.

The accompanying header file `inc/darrayAlgs.h` provides some useful algorithms for common operations such as searching, sorting or iterating.

This Readme provides some usage notes. The more detailed information is in the header files.

## GENERAL
Most functions return a DarrayStatus enum value. Possible return values are:
- DARRAY_OK: the operation succeded
- DARRAY_ERROR_ALLOCATION: a malloc or realloc call failed
- DARRAY_ERROR_NULL: at least one argument was NULL when it shouldn't have been
- DARRAY_ERROR_BOUNDS: A given index was out of range of the darray
- DARRAY_ERROR_INVALID: An input was given in a way that the library cannot accept
- DARRAY_NOT_FOUND: (used by find operations in darrayAlgs) no matching element was found

The struct members should not be accessed directly. Always use the apropriate function call.

The darray does not provide thread safety. It is up to you to lock accesses where apropriate.

## MEMORY
Create a new darray object using `Darray variable_name`. Do not initialize it manually. Instead, use `darrayInit(Darray* self, size_t initial_size, size_t element_size)` this sets up the darray to have initial_size elements of size element_size (It is recommended you use sizeof(DATA_TYPE) as element_size). Some functions in darrayAlgs require an uninitialized darray and initialize it for you.
Unless specifically requested, it is undefined behavior to pass an uninitialized darray to a function.

You can release the darrays resources using `darrayDestroy(Darry*)`. calling this on the same darray multiple times is harmless. Passing a darray to a function after it has been destroyed is equivalent to passing an uninitialized one (i.e. okay only when explicitly expected).

Copying the darray struct creates a shallow copy, i.e. the elements are shared. Be careful with this as it could result in stale metadata causing undefined behavior. You can create a deep copy (i.e. same values, but seperate memory) usind `darrayDeepCopy()`.

## SIZE & CAPACITY
Size always refers to the number of elements in use. Capacity alway refers to the number of elements already allocated for.
If the darray is full, it will automatically double its size upon the next operation that adds an element. If an operation causes it to be less than half full, it will shrink to half the size (note that bulk deletion, i.e. with `darrayEraseAll()` will still only halve the capacity so erasing from a 16 element darray will shrink it to capacity 8, even though it has 0 elements.)
You can use `darrayReserve()` to guarantee a minimum for capacity.

## STRUCTURE
You can add and remove elements to / from the front and the back. For `darrayPushBack()` and `darrayPushFront()`, you need the value you want to store in a local variable, and pass a pointer to that variable. `darrayInsertAt()` works similarly.
Similarly, for `darrayPopBackInto()` and `darrayPopFrontInto()`, you need to provide a pointer as the destination.

## ERASING
`darrayEraseFromTo()` erases within the given indecies (including both indices themselves). The other functions of the erase family are aliases that fix the start and / or the end of the erase:
- `darrayEraseFrom(start)` is equivalent to `darrayEraseFromTo(start, [LAST ELEMENT'S INDEX])
- `darrayEraseTo(end)` is equivalent to `darrayEraseFromTo(0, end)
- `darrayEraseAll()` and `darrayClear()` are equivalent to `darrayEraseFromTo(0, [LAST ELEMENT'S INDEX])
- `darrayEraseAt(index)`is equivalent to `darrayEraseFromTo(index, index`

## ACCESS
These allow you to read or write single elements of the darray. Like the push and pop methods, you need to provide a variable buffer to read to / write from.

`darrayData()` allows you to get a direct pointer to the elements. This should be done carefully as any operation that adds or removes elements has a chance to reallocate the data, making the pointer invalid


## SEARCHING
findFirst example usage:

```c
bool condition(const void* element, const void* data) {
    return (*(size_t*) element == *(size_t*) data);
}

size_t target = 2;
DarrayStatus res = darrayFindFirst(&d, condition, &temp, &target);
if (res == DARRAY_OK) {
    //do something with index of value 2
}

size_t target = 3;
DarrayStatus res = darrayFindFirst(&d, condition, &temp, &target);
if (res == DARRAY_OK) {
    //do something with index of value 3
}
```

`darrayBinarySearch()` assumes unique values and ascending sorting. This is not verified, as doing so would defeat the purpose of using binary search in the first place by degrading the runtime from O(log(n)) to O(n).

## SETLIKE OPERATONS
These functions require sorted darrays to maintain linear runtimes.
