add_library(message_buffer INTERFACE)
target_include_directories(
    message_buffer
    INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)
target_link_libraries(
    message_buffer
    INTERFACE
        status_or
)

if (${PROJECT_IS_TOP_LEVEL})

add_subdirectory(tests)

endif()
