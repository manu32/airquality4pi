
file(GLOB SOURCES *.cpp)
file(GLOB HEADERS *.h)

set(CMAKE_CXX_STANDARD 17)

add_executable(${PROJECT_NAME})

target_sources(${PROJECT_NAME} PRIVATE ${HEADERS} ${SOURCES})

target_link_libraries(${PROJECT_NAME} ${CONAN_LIBS})