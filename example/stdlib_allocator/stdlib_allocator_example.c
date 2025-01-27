#include <stdio.h>
#include <stdlib.h>

#include <julian_pfaul/allocator.h>

int main(void) {
    struct allocator stdalloc = allocator_create(malloc, free);

    size_t* numbers = allocator_allocate(stdalloc, sizeof(size_t) * 64, NULL);

    for (size_t index = 0; index < 64; ++index) {
        numbers[index] = index;
    }

    for (size_t index = 0; index < 64; ++index) {
        printf("%lu\n", numbers[index]);
    }

    allocator_deallocate(stdalloc, numbers, NULL);

    return 0;
}
