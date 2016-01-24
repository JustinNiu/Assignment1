cmake_minimum_required (VERSION 3.0)
project (Assign1
        VERSION 0.0.0.1)

add_subdirectory(${CMAKE_SOURCE_DIR}/src/${PROJECT_NAME} "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Exec")

# output version number variable
message(STATUS ${PROJECT_NAME} Version: ${PROJECT_VERSION})
message(STATUS "")

