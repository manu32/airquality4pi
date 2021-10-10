
cmake_minimum_required(VERSION 3.13)

#   enable_testing()

set(CMAKE_CXX_STANDARD 17)

project(airquality4pi)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_subdirectory(src)
add_subdirectory(test/unit)