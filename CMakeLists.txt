# 3.0: version
cmake_minimum_required(VERSION 3.0 FATAL_ERROR)

project(argparse LANGUAGES CXX VERSION 0.1.0.0)

set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD 11)

add_subdirectory(examples)

# "this command should be in the source directory root for CTest to find the test file"
enable_testing() 
add_subdirectory(test)
