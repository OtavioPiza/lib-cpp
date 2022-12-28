
add_executable(main main.cc)
add_test(
    NAME default_trie_test
    COMMAND main
)

target_link_libraries(
    main
    PRIVATE default_trie
)

target_link_directories(
    main
    PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/../
)
