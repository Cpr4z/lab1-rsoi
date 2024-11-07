cmake_minimum_required(VERSION 3.28.3)

list( APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)
include(common)

project(MyWebProject)
include(libs)

add_subdirectory(base)
add_subdirectory(network_library)
add_subdirectory(person_backend)