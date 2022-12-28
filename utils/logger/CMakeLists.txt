add_library(logger SHARED)

set_target_properties(
    logger
    PROPERTIES
        LINKER_LANGUAGE CXX
)

target_sources(
    logger
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_include_directories(
    logger
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)
