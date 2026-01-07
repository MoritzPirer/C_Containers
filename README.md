findFirst example usage:

```c
bool condition(const void* element, const void* data) {
    return (*(size_t*) element == *(size_t*) data);
}

size_t target = 2;
DarrayStatus res = darrayFindFirst(&d, condition, &temp, &target);
if (res = DARRAY_OK) {
    //do something with index of value 2
}

size_t target = 3;
DarrayStatus res = darrayFindFirst(&d, condition, &temp, &target);
if (res = DARRAY_OK) {
    //do something with index of value 3
}
```