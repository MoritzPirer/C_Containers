#include <printf.h>
#include "../../../inc/vec/vec.h"
#include "../vec_internal.h"

void vec_debug(const vec_t* self) {
    if (self == NULL) {
        return;
    }

    printf("=========\n");
    printf("====\n");
    printf("size: %zu\n", self->size);
    printf("capacity: %zu\n", self->capacity);
    printf("item size: %zu\n", self->item_size);

    for (size_t i = 0; i < self->size; i++) {
        printf("vec[%zu] = %d\n", i, *(int*) _vec_nth_element(self, i));
    }

    printf("iterator version: %zu\n", self->iterator_version);
    printf("=========\n");
}
