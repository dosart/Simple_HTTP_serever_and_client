###################################################################################################
##
##      Information about the project
##
###################################################################################################

cmake_minimum_required(VERSION 3.16)

set(PROJECT_NAME echo_server_and_client)
project(${PROJECT_NAME} VERSION 1.0.0
        DESCRIPTION "Simple implementation of a TCP echo server and client using BSD sockets"
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
set(SERVER_NAME server)
set(CLIENT_NAME client)

add_executable(${SERVER_NAME})
set_target_properties(
        ${SERVER_NAME} PROPERTIES
        C_STANDARD 11
        C_STANDARD_REQUIRED ON
)

target_sources(
        ${SERVER_NAME}
        PRIVATE
        src/main_server.c
        src/wrappers.c
        src/methods.c 
        src/utils.c
)
target_include_directories(
        ${SERVER_NAME}
        PRIVATE
        ${PROJECT_INCLUDE_DIR}
)

add_executable(${CLIENT_NAME})
set_target_properties(
        ${CLIENT_NAME} PROPERTIES
        C_STANDARD 11
        C_STANDARD_REQUIRED ON
)

target_sources(
        ${CLIENT_NAME}
        PRIVATE
        src/main_client.c
        src/wrappers.c
)
target_include_directories(
        ${CLIENT_NAME}
        PRIVATE
        ${PROJECT_INCLUDE_DIR}
)