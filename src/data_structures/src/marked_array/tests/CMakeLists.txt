# Default trie tests.
set(MARKED_ARRAY_TEST_LIBS marked_array testing)

# Default try add tests.
add_executable(marked_array_test src/marked_array_test.cc)
add_test(NAME marked_array_test COMMAND marked_array_test)
target_link_libraries(marked_array_test PRIVATE ${MARKED_ARRAY_TEST_LIBS})
target_link_directories(marked_array_test PRIVATE ${PROJECT_SOURCE_DIR})

