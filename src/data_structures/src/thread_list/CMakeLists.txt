add_library(thread_list SHARED)

target_sources(thread_list PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/thread_list.cc)
target_include_directories(
    thread_list
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)
