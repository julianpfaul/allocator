#pragma once

#include <stddef.h>

typedef typeof(void* (*)(size_t sz))                          allocate_func_t;
typedef typeof(void* (*)(void* state, size_t sz))             allocate_func_with_state_t;
typedef typeof(void* (*)(size_t sz, void* args))              allocate_func_extended_t;
typedef typeof(void* (*)(void* state, size_t sz, void* args)) allocate_func_extended_with_state_t;

typedef typeof(void (*)(void* ptr))                          deallocate_func_t;
typedef typeof(void (*)(void* state, void* ptr))             deallocate_func_with_state_t;
typedef typeof(void (*)(void* ptr, void* args))              deallocate_func_extended_t;
typedef typeof(void (*)(void* state, void* ptr, void* args)) deallocate_func_extended_with_state_t;

enum allocator_function_type : unsigned char {
    ALLOCATOR_FUNCTION_SIMPLE              = 0,
    ALLOCATOR_FUNCTION_WITH_STATE          = 1,
    ALLOCATOR_FUNCTION_EXTENDED            = 2,
    ALLOCATOR_FUNCTION_EXTENDED_WITH_STATE = 3
};

struct allocate_function {
    enum allocator_function_type type;
    void*                        state;

    union {
        allocate_func_t                     simple;
        allocate_func_with_state_t          with_state;
        allocate_func_extended_t            extended;
        allocate_func_extended_with_state_t extended_with_state;
    };
};

struct allocate_function allocate_function_create_simple(allocate_func_t func);
struct allocate_function allocate_function_create_with_state(allocate_func_with_state_t func, void* state);
struct allocate_function allocate_function_create_extended(allocate_func_extended_t func);
struct allocate_function allocate_function_create_extended_with_state(allocate_func_extended_with_state_t func, void* state);

void* allocate_function_call(struct allocate_function, size_t sz, void* extended_args);

struct deallocate_function {
    enum allocator_function_type type;
    void*                        state;

    union {
        deallocate_func_t                     simple;
        deallocate_func_with_state_t          with_state;
        deallocate_func_extended_t            extended;
        deallocate_func_extended_with_state_t extended_with_state;
    };
};

struct deallocate_function deallocate_function_create_simple(deallocate_func_t func);
struct deallocate_function deallocate_function_create_with_state(deallocate_func_with_state_t func, void* state);
struct deallocate_function deallocate_function_create_extended(deallocate_func_extended_t func);
struct deallocate_function deallocate_function_create_extended_with_state(deallocate_func_extended_with_state_t func, void* state);

void deallocate_function_call(struct deallocate_function, void* ptr, void* extended_args);

struct allocator {
    struct allocate_function   allocate;
    struct deallocate_function deallocate;
};

struct allocator allocator_create(allocate_func_t allocate_func, deallocate_func_t deallocate_func);
struct allocator allocator_create_with_state(allocate_func_with_state_t allocate_func, deallocate_func_with_state_t deallocate_func, void* state);
struct allocator allocator_create_extended(allocate_func_extended_t allocate_func, deallocate_func_extended_t deallocate_func);
struct allocator allocator_create_extended_with_state(allocate_func_extended_with_state_t allocate_func, deallocate_func_extended_with_state_t deallocate_func, void* state);

struct allocator allocator_create_custom(struct allocate_function, struct deallocate_function);

void* allocator_allocate(struct allocator, size_t sz, void* extended_args);
void  allocator_deallocate(struct allocator, void* ptr, void* extended_args);
