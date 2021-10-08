
file(GLOB SOURCES */*.cpp *.cpp)
file(GLOB HEADERS */*.h *.h)

if("${ARCH}" STREQUAL "armv7")
    add_definitions(-lwiringPi -lpthread)
    find_library(wiringPi_LIB wiringPi)
    set(ARM_SPECIFIC_LIBS ${wiringPi_LIB})
endif()

set(CMAKE_CXX_STANDARD 17)

add_executable(${PROJECT_NAME})

target_sources(${PROJECT_NAME} PRIVATE ${HEADERS} ${SOURCES})

message(STATUS ${ARM_SPECIFIC_LIBS})

target_link_libraries(${PROJECT_NAME} ${CONAN_LIBS} ${ARM_SPECIFIC_LIBS})