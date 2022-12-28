cmake_minimum_required(VERSION 3.22.1)

add_library(data_structures INTERFACE)
target_include_directories(data_structures INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(
    data_structures
    INTERFACE
        default_trie
)

add_subdirectory(default_trie default_trie)
