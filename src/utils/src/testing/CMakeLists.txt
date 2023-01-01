add_library(testing INTERFACE)
target_include_directories(testing INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(testing INTERFACE logger)
target_link_directories(testing INTERFACE ${PROJECT_SOURCE_DIR})
