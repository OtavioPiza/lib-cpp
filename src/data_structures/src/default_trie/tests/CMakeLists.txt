# Default trie tests.
set(DEFAULT_TRIE_TEST_LIBS default_trie testing)

# Default try add tests.
add_executable(default_trie_test src/default_trie_test.cc)
add_test(NAME default_trie_test COMMAND default_trie_test)
target_link_libraries(default_trie_test PRIVATE ${DEFAULT_TRIE_TEST_LIBS})
target_link_directories(default_trie_test PRIVATE ${PROJECT_SOURCE_DIR})

