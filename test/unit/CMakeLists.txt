
project(unit_test)

file(GLOB SOURCES *.cpp)

add_executable(${PROJECT_NAME})

target_sources(${PROJECT_NAME} PRIVATE ${SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/src)

target_link_libraries(${PROJECT_NAME} PRIVATE ${CONAN_LIBS} dht_sensor)

add_test(NAME UnitTests
 COMMAND ${PROJECT_NAME}
 WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)