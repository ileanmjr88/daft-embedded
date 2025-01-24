cmake_minimum_required(VERSION 3.10)

# Set the project name
project(i2cdriver VERSION 1.0 LANGUAGES C)

# Specify the C standard
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)

# Add the executable
add_executable(i2cdriver src/main.c src/i2c_driver.c src/checks.c)

# Include directories
include_directories(include)
