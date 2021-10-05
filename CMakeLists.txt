
cmake_minimum_required(VERSION 3.13)

project(airquality4pi)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_subdirectory(src)