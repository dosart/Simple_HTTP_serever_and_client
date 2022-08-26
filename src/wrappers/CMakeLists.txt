cmake_minimum_required(VERSION 3.16)

set(PROJECT_NAME wrappers)
project(${PROJECT_NAME} VERSION 0.0.1 LANGUAGES C)

add_library(${PROJECT_NAME} STATIC wrappers.c wrappers.h)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

set_target_properties(${PROJECT_NAME} PROPERTIES
        C_STANDARD 11
        C_STANDARD_REQUIRED ON)
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
        -Wsign-conversion)