cmake_minimum_required(VERSION 3.22.1)

project(libcc)

set(CMAKE_CXX_STANDARD 20)

add_library(${PROJECT_NAME} INTERFACE)

target_include_directories(${PROJECT_NAME} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(
    ${PROJECT_NAME}
    INTERFACE 
        data_structures
        utils
)

if (${PROJECT_IS_TOP_LEVEL})
enable_testing()
endif()

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/data_structures data_structures)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/utils utils)
