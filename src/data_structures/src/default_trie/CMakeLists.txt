cmake_minimum_required(VERSION 3.22.1)

add_library(default_trie INTERFACE)
target_include_directories(default_trie INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_subdirectory(tests)
