
#define MAX(x, y) (x > y? x : y)
#define MIN(x, y) (x < y? x : y)

inline void swap(size_t* a, size_t* b) {
    size_t temp = *a;
    *a = *b;
    *b = temp;
}