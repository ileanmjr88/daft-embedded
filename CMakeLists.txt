cmake_minimum_required(VERSION 3.10)

# Set the project name
project(i2cdriver VERSION 1.0)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add the executable
add_executable(i2cdriver main.c)

# Include directories
include_directories(include)

# Link libraries
target_link_libraries(i2cdriver PRIVATE some_library)