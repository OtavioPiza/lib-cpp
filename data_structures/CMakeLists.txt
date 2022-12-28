cmake_minimum_required(VERSION 3.22.1)

add_library(data_structures INTERFACE)

add_subdirectory(default_trie default_trie)

target_link_libraries(
    data_structures
    INTERFACE default_trie
)
