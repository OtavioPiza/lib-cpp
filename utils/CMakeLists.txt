cmake_minimum_required(VERSION 3.22.1)

add_library(utils INTERFACE)

add_subdirectory(logger)

target_link_libraries(
    utils
    INTERFACE logger
)
