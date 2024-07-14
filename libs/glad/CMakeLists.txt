cmake_minimum_required(VERSION 3.26)
project(glad LANGUAGES C)

add_library(glad STATIC src/gl.c)
target_include_directories(glad PUBLIC include/)

add_library(glad::glad ALIAS glad)