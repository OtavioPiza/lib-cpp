# Default trie tests.
set(message_buffer_TEST_LIBS message_buffer testing absl::status)

# Default try add tests.
add_executable(message_buffer_test src/message_buffer_test.cc)
add_test(NAME message_buffer_test COMMAND message_buffer_test)
target_link_libraries(message_buffer_test PRIVATE ${message_buffer_TEST_LIBS})
target_link_directories(message_buffer_test PRIVATE ${PROJECT_SOURCE_DIR})
