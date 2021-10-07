
file(GLOB SOURCES */*.cpp *.cpp)
file(GLOB HEADERS */*.h *.h)

add_definitions(-lwiringPi -lpthread)
find_library(wiringPi_LIB wiringPi)

set(CMAKE_CXX_STANDARD 17)

add_executable(${PROJECT_NAME})

target_sources(${PROJECT_NAME} PRIVATE ${HEADERS} ${SOURCES})

target_link_libraries(${PROJECT_NAME} ${CONAN_LIBS} ${wiringPi_LIB})