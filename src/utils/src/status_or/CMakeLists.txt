add_library(status_or SHARED)

target_sources(status_or PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/status_or.cc)
target_include_directories(
    status_or
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)
