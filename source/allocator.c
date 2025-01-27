#include <julian_pfaul/allocator.h>

// ALLOCATE

struct allocate_function allocate_function_create_simple(allocate_func_t func) {
    struct allocate_function allocate_function;
    allocate_function.type   = ALLOCATOR_FUNCTION_SIMPLE;
    allocate_function.state  = NULL;
    allocate_function.simple = func;

    return allocate_function;
}

struct allocate_function allocate_function_create_with_state(allocate_func_with_state_t func, void* state) {
    struct allocate_function allocate_function;
    allocate_function.type       = ALLOCATOR_FUNCTION_WITH_STATE;
    allocate_function.state      = state;
    allocate_function.with_state = func;

    return allocate_function;
}

struct allocate_function allocate_function_create_extended(allocate_func_extended_t func) {
    struct allocate_function allocate_function;
    allocate_function.type     = ALLOCATOR_FUNCTION_EXTENDED;
    allocate_function.state    = NULL;
    allocate_function.extended = func;

    return allocate_function;
}

struct allocate_function allocate_function_create_extended_with_state(allocate_func_extended_with_state_t func, void* state) {
    struct allocate_function allocate_function;
    allocate_function.type                = ALLOCATOR_FUNCTION_EXTENDED_WITH_STATE;
    allocate_function.state               = state;
    allocate_function.extended_with_state = func;

    return allocate_function;
}

// DEALLOCATE

struct deallocate_function deallocate_function_create_simple(deallocate_func_t func) {
    struct deallocate_function deallocate_function;
    deallocate_function.type   = ALLOCATOR_FUNCTION_SIMPLE;
    deallocate_function.state  = NULL;
    deallocate_function.simple = func;

    return deallocate_function;
}

struct deallocate_function deallocate_function_create_with_state(deallocate_func_with_state_t func, void* state) {
    struct deallocate_function deallocate_function;
    deallocate_function.type       = ALLOCATOR_FUNCTION_WITH_STATE;
    deallocate_function.state      = state;
    deallocate_function.with_state = func;

    return deallocate_function;
}

struct deallocate_function deallocate_function_create_extended(deallocate_func_extended_t func) {
    struct deallocate_function deallocate_function;
    deallocate_function.type     = ALLOCATOR_FUNCTION_EXTENDED;
    deallocate_function.state    = NULL;
    deallocate_function.extended = func;

    return deallocate_function;
}

struct deallocate_function deallocate_function_create_extended_with_state(deallocate_func_extended_with_state_t func, void* state) {
    struct deallocate_function deallocate_function;
    deallocate_function.type                = ALLOCATOR_FUNCTION_EXTENDED_WITH_STATE;
    deallocate_function.state               = state;
    deallocate_function.extended_with_state = func;

    return deallocate_function;
}

struct allocator allocator_create(allocate_func_t allocate_func, deallocate_func_t deallocate_func) {
    struct allocator allocator;
    allocator.allocate   = allocate_function_create_simple(allocate_func);
    allocator.deallocate = deallocate_function_create_simple(deallocate_func);

    return allocator;
}

struct allocator allocator_create_with_state(allocate_func_with_state_t allocate_func, deallocate_func_with_state_t deallocate_func, void* state) {
    struct allocator allocator;
    allocator.allocate   = allocate_function_create_with_state(allocate_func, state);
    allocator.deallocate = deallocate_function_create_with_state(deallocate_func, state);

    return allocator;
}

struct allocator allocator_create_extended(allocate_func_extended_t allocate_func, deallocate_func_extended_t deallocate_func) {
    struct allocator allocator;
    allocator.allocate   = allocate_function_create_extended(allocate_func);
    allocator.deallocate = deallocate_function_create_extended(deallocate_func);

    return allocator;
}

struct allocator allocator_create_extended_with_state(allocate_func_extended_with_state_t allocate_func, deallocate_func_extended_with_state_t deallocate_func, void* state) {
    struct allocator allocator;
    allocator.allocate   = allocate_function_create_extended_with_state(allocate_func, state);
    allocator.deallocate = deallocate_function_create_extended_with_state(deallocate_func, state);

    return allocator;
}

struct allocator allocator_create_custom(struct allocate_function alloc, struct deallocate_function dealloc) {
    struct allocator allocator;
    allocator.allocate   = alloc;
    allocator.deallocate = dealloc;

    return allocator;
}

void* allocate_function_call(struct allocate_function alloc, size_t sz, void* extended_args) {
    switch (alloc.type) {
        case ALLOCATOR_FUNCTION_SIMPLE: return alloc.simple(sz);
        case ALLOCATOR_FUNCTION_WITH_STATE: return alloc.with_state(alloc.state, sz);
        case ALLOCATOR_FUNCTION_EXTENDED: return alloc.extended(sz, extended_args);
        case ALLOCATOR_FUNCTION_EXTENDED_WITH_STATE: return alloc.extended_with_state(alloc.state, sz, extended_args);
    }

    return NULL;
}

void deallocate_function_call(struct deallocate_function dealloc, void* ptr, void* extended_args) {
    switch (dealloc.type) {
        case ALLOCATOR_FUNCTION_SIMPLE:
            dealloc.simple(ptr);
            break;
        case ALLOCATOR_FUNCTION_WITH_STATE:
            dealloc.with_state(dealloc.state, ptr);
            break;
        case ALLOCATOR_FUNCTION_EXTENDED:
            dealloc.extended(ptr, extended_args);
            break;
        case ALLOCATOR_FUNCTION_EXTENDED_WITH_STATE:
            dealloc.extended_with_state(dealloc.state, ptr, extended_args);
            break;
    }
}

void* allocator_allocate(struct allocator allocator, size_t sz, void* extended_args) {
    return allocate_function_call(allocator.allocate, sz, extended_args);
}

void allocator_deallocate(struct allocator allocator, void* ptr, void* extended_args) {
    return deallocate_function_call(allocator.deallocate, ptr, extended_args);
}
