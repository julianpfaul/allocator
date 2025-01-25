#pragma once
#include <stddef.h>

typedef typeof(void*(*)(size_t)) allocate_func_t;
typedef typeof(void (*)(void*))  deallocate_func_t;

struct allocator {
    allocate_func_t   allocate;
    deallocate_func_t deallocate;
};

struct allocator allocator_create(allocate_func_t, deallocate_func_t);

void* allocator_allocate(struct allocator, size_t);
void allocator_deallocate(struct allocator, void*);
