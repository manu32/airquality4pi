
add_subdirectory(dht_sensor)

file(GLOB SOURCES */*.cpp *.cpp)
file(GLOB HEADERS */*.h *.h)

# set arm specific libraries 
if("${ARCH}" STREQUAL "armv7")
    add_definitions(-lwiringPi -lpthread)
    find_library(wiringPi_LIB wiringPi)
    set(ARM_SPECIFIC_LIBS ${wiringPi_LIB})
endif()

set(CMAKE_CXX_STANDARD 17)

add_executable(${PROJECT_NAME})

# add sources to target
target_sources(${PROJECT_NAME} PRIVATE ${HEADERS} ${SOURCES})

# link libraries to target
target_link_libraries(${PROJECT_NAME} ${CONAN_LIBS} ${ARM_SPECIFIC_LIBS} dht_sensor)