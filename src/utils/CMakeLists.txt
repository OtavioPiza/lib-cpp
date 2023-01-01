cmake_minimum_required(VERSION 3.22.1)

add_library(utils INTERFACE)

target_include_directories(utils INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(
    utils
    INTERFACE
        logger
        status_or
        testing
)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/logger logger)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/status_or status_or)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/testing testing)
