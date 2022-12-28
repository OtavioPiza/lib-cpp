# Default trie tests.
set(DEFAULT_TRIE_TEST_LIBS default_trie logger)

# Default try add tests.
add_executable(add_test add_test.cc)
add_test(NAME add_test COMMAND add_test)
target_link_libraries(add_test PRIVATE ${DEFAULT_TRIE_TEST_LIBS})
target_link_directories(add_test PRIVATE ${PROJECT_SOURCE_DIR})

# Default trie constructor tests.
add_executable(constructor_test constructor_test.cc)
add_test(NAME constructor_test COMMAND constructor_test)
target_link_libraries(constructor_test PRIVATE ${DEFAULT_TRIE_TEST_LIBS})
target_link_directories(constructor_test PRIVATE ${PROJECT_SOURCE_DIR})

# Default trie find tests.
add_executable(get_test get_test.cc)
add_test(NAME get_test COMMAND get_test)
target_link_libraries(get_test PRIVATE ${DEFAULT_TRIE_TEST_LIBS})
target_link_directories(get_test PRIVATE ${PROJECT_SOURCE_DIR})

# Default trie remove tests.
add_executable(remove_test remove_test.cc)
add_test(NAME remove_test COMMAND remove_test)
target_link_libraries(remove_test PRIVATE ${DEFAULT_TRIE_TEST_LIBS})
target_link_directories(remove_test PRIVATE ${PROJECT_SOURCE_DIR})
