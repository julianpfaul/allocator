#include <julian_pfaul/allocator.h>

struct allocator allocator_create(const allocate_func_t   alloc_func, void*   alloc_args,
                                  const deallocate_func_t dealloc_func, void* dealloc_args) {
    struct allocator allocator;
    allocator.allocate_args = alloc_args;
    allocator.deallocate_args = dealloc_args;
    allocator.allocate   = alloc_func;
    allocator.deallocate = dealloc_func;
    return allocator;
}

void* allocator_allocate(struct allocator allocator, size_t size) {
    return allocator.allocate(allocator.allocate_args, size);
}

void allocator_deallocate(struct allocator allocator, void* ptr) {
    allocator.deallocate(allocator.deallocate_args, ptr);
}
