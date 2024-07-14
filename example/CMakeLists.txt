cmake_minimum_required(VERSION 3.27)
project(example LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)


add_executable(example src/main.cpp src/main.hpp)
target_include_directories(example PUBLIC src/)
target_link_libraries(example bdengine::bdengine)

