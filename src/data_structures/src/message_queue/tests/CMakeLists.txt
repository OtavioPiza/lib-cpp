# Default trie tests.
set(MESSAGE_QUEUE_TEST_LIBS message_queue testing)

# Default try add tests.
add_executable(message_queue_test src/message_queue_test.cc)
add_test(NAME message_queue_test COMMAND message_queue_test)
target_link_libraries(message_queue_test PRIVATE ${MESSAGE_QUEUE_TEST_LIBS})
target_link_directories(message_queue_test PRIVATE ${PROJECT_SOURCE_DIR})
