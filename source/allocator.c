#include <julian_pfaul/allocator.h>

struct allocator allocator_create(const allocate_func_t alloc_func, const deallocate_func_t dealloc_func) {
    struct allocator allocator;
    allocator.allocate   = alloc_func;
    allocator.deallocate = dealloc_func;
    return allocator;
}

void* allocator_allocate(struct allocator allocator, size_t size) {
    return allocator.allocate(size);
}

void allocator_deallocate(struct allocator allocator, void* ptr) {
    allocator.deallocate(ptr);
}
