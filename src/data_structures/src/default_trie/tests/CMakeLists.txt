# Default trie tests.
set(DEFAULT_TRIE_TEST_LIBS default_trie logger)

# Default try add tests.
add_executable(insert_test insert_test.cc)
add_test(NAME insert_test COMMAND insert_test)
target_link_libraries(insert_test PRIVATE ${DEFAULT_TRIE_TEST_LIBS})
target_link_directories(insert_test PRIVATE ${PROJECT_SOURCE_DIR})

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

# Default trie remove tests.
add_executable(update_default_return_test update_default_return_test.cc)
add_test(NAME update_default_return_test COMMAND update_default_return_test)
target_link_libraries(update_default_return_test PRIVATE ${DEFAULT_TRIE_TEST_LIBS})
target_link_directories(update_default_return_test PRIVATE ${PROJECT_SOURCE_DIR})
