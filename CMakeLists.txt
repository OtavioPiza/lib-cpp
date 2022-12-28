cmake_minimum_required(VERSION 3.22.1)

project(libcc)

add_library(${PROJECT_NAME} INTERFACE)

enable_testing()

add_subdirectory(data_structures data_structures)
add_subdirectory(utils utils)

target_link_libraries(
    ${PROJECT_NAME}
    INTERFACE 
        data_structures
        utils
)
