cmake_minimum_required(VERSION 3.14)
project(doode)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin)


set(BOX2D_BUILD_TESTBED OFF)
set(BOX2D_BUILD_UNIT_TESTS OFF)

add_subdirectory(SFML)
add_subdirectory(entt)
add_subdirectory(spdlog)
add_subdirectory(box2d) 
add_subdirectory(doode)
