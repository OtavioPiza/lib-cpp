cmake_minimum_required(VERSION 3.22.1)

project(default_try)

add_library(${PROJECT_NAME} SHARED)

target_sources(
    ${PROJECT_NAME} 
    PRIVATE
        src/default_trie.cc
)

target_include_directories(
    ${PROJECT_NAME}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include

)
