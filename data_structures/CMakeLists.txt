cmake_minimum_required(VERSION 3.22.1)

project(data_structures)

add_library(${PROJECT_NAME} INTERFACE)

add_subdirectory(default_trie default_trie)

target_link_libraries(
    ${PROJECT_NAME}
    INTERFACE 
        default_trie
)
