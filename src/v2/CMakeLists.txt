cmake_minimum_required(VERSION 3.16)

set(PROJECT_NAME v2)
set(WRAPPERS_LIB wrappers)
project(${PROJECT_NAME} VERSION 0.0.1 LANGUAGES C)

add_executable(client client.c)
add_executable(server server.c)

target_link_libraries(client ${WRAPPERS_LIB})
target_link_libraries(server ${WRAPPERS_LIB})

set_target_properties(${PROJECT_NAME} PROPERTIES C_STANDARD 11 C_STANDARD_REQUIRED ON)
     
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