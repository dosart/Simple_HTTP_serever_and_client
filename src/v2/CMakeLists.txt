cmake_minimum_required(VERSION 3.16)
project(${PROJECT_NAME} VERSION 0.0.1 LANGUAGES C)

set(PROJECT_NAME v2)
set(WRAPPERS_LIB wrappers)

set(CLIENT client_v2)
set(SERVER server_v2)

add_executable(${CLIENT} client.c)
target_link_libraries(${CLIENT} ${WRAPPERS_LIB})
set_target_properties(${CLIENT} PROPERTIES C_STANDARD 11 C_STANDARD_REQUIRED ON)

add_executable(${SERVER} server.c)
target_link_libraries(${SERVER} ${WRAPPERS_LIB})
set_target_properties(${SERVER} PROPERTIES C_STANDARD 11 C_STANDARD_REQUIRED ON)
     
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
