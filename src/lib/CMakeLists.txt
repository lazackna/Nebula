cmake_minimum_required(VERSION 3.10.2)
project(lib LANGUAGES C CXX)


include(FetchContent)

add_subdirectory(glad)
add_subdirectory(glfw)
