#include <stddef.h>
#define MAX(x, y) (x > y? x : y)
#define MIN(x, y) (x < y? x : y)

void swap(size_t* a, size_t* b);

size_t next_power_of_two(size_t n);
size_t previous_power_of_two(size_t n);