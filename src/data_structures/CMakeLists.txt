add_library(data_structures INTERFACE)

target_include_directories(data_structures INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(
    data_structures
    INTERFACE
        default_trie
        marked_array
        message_queue
)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/default_trie default_trie)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/marked_array marked_array)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/message_queue message_queue)
