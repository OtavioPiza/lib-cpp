add_library(message_queue SHARED)

# Library sources and headers.
target_sources(
    message_queue
    PRIVATE 
        ${CMAKE_CURRENT_SOURCE_DIR}/src/message_queue.cc
)

target_include_directories(
    message_queue
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Link dependencies.
target_link_libraries(
    message_queue
    PRIVATE
        status_or
)

if (${PROJECT_IS_TOP_LEVEL})

add_subdirectory(tests)

endif()
