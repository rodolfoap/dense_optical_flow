cmake_minimum_required(VERSION 3.10)
project(denseflow)

# Force C++11
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Equivalent to (CFLAGS) -g
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
message(STATUS "Binary will go to: ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")

# Equivalent to (CFLAGS) -g
set(CMAKE_C_FLAGS "-g")

add_library(denseflow STATIC denseflow.cpp)
add_executable(main main.cpp)

# OPENCV ####################################
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
target_link_libraries(main ${OpenCV_LIBS} denseflow)
