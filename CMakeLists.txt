cmake_minimum_required(VERSION 3.10)
project(allocator C)

set(CMAKE_C_STANDARD 11)

file(GLOB_RECURSE SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/source/*.c")
file(GLOB_RECURSE HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/include/*.h")

# Create a library target without the namespace in the name
add_library(allocator STATIC
        ${SOURCES}
        ${HEADERS}
)

# Specify the namespace for the target
set_target_properties(allocator PROPERTIES
        VERSION 1.0
)

target_include_directories(allocator PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Set the include directories for the target
target_include_directories(allocator
        INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

install(TARGETS allocator
        EXPORT julian_pfaul_allocator
        ARCHIVE DESTINATION lib
)

install(EXPORT julian_pfaul_allocator
        FILE julian_pfaul_allocator.cmake
        NAMESPACE julian_pfaul::
        DESTINATION lib/cmake/allocator
)