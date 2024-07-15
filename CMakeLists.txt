cmake_minimum_required(VERSION 3.27)
project(bdengine LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

add_subdirectory(libs/)

find_package(glfw3 CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(eventpp CONFIG REQUIRED)

add_library(bdengine STATIC src/bde/bde.cpp src/bde/bde.hpp
        src/bde/math.cpp
        src/bde/math.hpp
        src/bde/render.cpp
        src/bde/render.hpp
        src/bde/colors.hpp
        src/bde/hal.cpp
        src/bde/hal.hpp
        src/bde/render/mesh.cpp
        src/bde/render/mesh.hpp
        src/bde/render/interfaces.hpp
        src/bde/utils.hpp
        src/bde/utils.cpp)
target_include_directories(bdengine PUBLIC src/)
target_link_libraries(bdengine PUBLIC glfw glm::glm spdlog::spdlog eventpp::eventpp glad::glad)

add_library(bdengine::bdengine ALIAS bdengine)

add_subdirectory(example/)
