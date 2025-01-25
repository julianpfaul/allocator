#pragma once
#include <stddef.h>

typedef typeof(void*(*)(void* args, size_t sz)) allocate_func_t;
typedef typeof(void (*)(void* args, void* ptr)) deallocate_func_t;

struct allocator {
    void*             allocate_args;
    void*             deallocate_args;
    allocate_func_t   allocate;
    deallocate_func_t deallocate;
};

struct allocator allocator_create(allocate_func_t, void* alloc_args, deallocate_func_t, void* dealloc_args);

void* allocator_allocate(struct allocator, size_t);

void allocator_deallocate(struct allocator, void*);
