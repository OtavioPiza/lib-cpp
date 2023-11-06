cmake_minimum_required(VERSION 3.18)
set(CMAKE_CXX_STANDARD 20)

project(libcc)


# Configure the abseil library.
if (NOT TARGET absl AND NOT ABLS_ADDED)
    set(ABSL_PROPAGATE_CXX_STD ON)
    set(ABSL_ADDED TRUE)

    # If a user has not specified a directory for abseil, then clone it from GitHub into lib/abseil-cpp.
    if (NOT DEFINED ABSL_DIR)
        # Set the directory to clone abseil into.
        set(ABSL_DIR ${CMAKE_CURRENT_SOURCE_DIR}/lib/abseil-cpp)

        # If the directory does not exist, then clone it otherwise pull from origin master.
        if (NOT EXISTS ${ABSL_DIR})
            message(STATUS "Cloning abseil into ${ABSL_DIR}")
            execute_process(COMMAND git clone https://github.com/abseil/abseil-cpp.git ${ABSL_DIR})

        else()
            message(STATUS "Updating abseil in ${ABSL_DIR}")
            execute_process(COMMAND git pull origin master WORKING_DIRECTORY ${ABSL_DIR})

        endif()

    endif()

    # Add abseil as a subdirectory with a build directory of build with the same c++ standard
    # as this project.
    add_subdirectory(${ABSL_DIR} ${CMAKE_CURRENT_BINARY_DIR}/abseil-cpp)
endif()


add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/data_structures data_structures)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/utils utils)


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
