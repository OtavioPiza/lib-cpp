add_library(marked_array SHARED)

target_sources(marked_array PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/marked_array.cc)
target_include_directories(
    marked_array
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)
