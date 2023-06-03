###################################################################################################
##
##      Information about the project
##
###################################################################################################

cmake_minimum_required(VERSION 3.16)

set(PROJECT_NAME server)
project(${PROJECT_NAME} VERSION 1.0.0
        DESCRIPTION "Server"
        LANGUAGES C
        )

###################################################################################################
##
##      Compilation options
##
###################################################################################################

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
###################################################################################################
##
##      Source files
##
###################################################################################################

set(PROJECT_INCLUDE_DIR include)

add_executable(${PROJECT_NAME})
set_target_properties(
        ${PROJECT_NAME} PROPERTIES
        C_STANDARD 11
        C_STANDARD_REQUIRED ON
)

target_sources(
        ${PROJECT_NAME}
        PRIVATE
        src/main.c
        src/wrappers.c
        src/methods.c 
        src/utils.c
)
target_include_directories(
        ${PROJECT_NAME}
        PRIVATE
        ${PROJECT_INCLUDE_DIR}
)
