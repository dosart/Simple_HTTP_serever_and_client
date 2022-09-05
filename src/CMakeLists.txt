cmake_minimum_required(VERSION 3.16)

set(PROJECT_NAME clients_and_servers)
project(${PROJECT_NAME} VERSION 0.0.1 LANGUAGES C)

add_subdirectory(wrappers)
add_subdirectory(v1)
add_subdirectory(v2)
add_subdirectory(v3)