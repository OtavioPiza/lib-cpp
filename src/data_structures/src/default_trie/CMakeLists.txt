add_library(default_trie INTERFACE)
target_include_directories(default_trie INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)

if (${PROJECT_IS_TOP_LEVEL})

add_subdirectory(tests)

endif()
