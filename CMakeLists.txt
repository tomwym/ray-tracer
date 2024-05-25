cmake_minimum_required(VERSION 3.22)

project(
    ray-tracer
    VERSION 1.0
    LANGUAGES CXX)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_BUILD_TYPE Debug)
# set(CMAKE_BUILD_TYPE Release)

find_package(GTest REQUIRED)
add_subdirectory(src)
add_subdirectory(tests)
