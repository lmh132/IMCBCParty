cmake_minimum_required(VERSION 3.10.0)
project(test VERSION 0.1.0 LANGUAGES C CXX)

# Add include directories
include_directories(${CMAKE_SOURCE_DIR}/external/asio/include include)

# Find all source files in src/
file(GLOB_RECURSE SOURCES src/*.cpp)

# Define the executable
add_executable(my_project ${SOURCES})
