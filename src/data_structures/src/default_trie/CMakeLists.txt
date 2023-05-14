add_library(default_trie SHARED)

target_sources(default_trie PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/default_trie.cc)
target_include_directories(
    default_trie 
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

if (${PROJECT_IS_TOP_LEVEL})

add_subdirectory(tests)

endif()
