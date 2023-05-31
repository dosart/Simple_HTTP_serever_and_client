cmake_minimum_required(VERSION 3.22)
project(srever C)

set(CMAKE_C_STANDARD 11)

add_compile_options(
        -Werror

        -Wall
        -Wextra
        -Wpedantic

        -Wcast-align
        -Wcast-qual
        -Wconversion
        -Wenum-compare
        -Wfloat-equal
        -Wredundant-decls
        -Wsign-conversion
)

add_executable(srever main.c wrappers.h wrappers.c methods.c methods.h)
