cmake_minimum_required(VERSION 3.12)
project(c-algorithm C)
set(CMAKE_C_STANDARD 11)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

enable_testing()

include_directories(include)

add_executable(array-list-test
        src/test.c
        test/collection/list/list-test.c
        test/collection/collection-test.c
        test/collection/list/array-list-test.c
        src/collection/list/array-list.c
        src/collection/list/list.c
        src/collection/list/list-iterator.c
        src/collection/collection.c
        )