add_library(logger SHARED)

target_sources(logger PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/logger.cc)
target_include_directories(
    logger
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)
