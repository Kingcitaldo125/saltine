cmake_minimum_required(VERSION 3.16)

project(saltine LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED true)

add_subdirectory(include/)
add_subdirectory(src/)

add_executable(saltine main.cpp)

target_link_libraries(saltine PRIVATE saltine)
target_include_directories(saltine ${CMAKE_SOURCE_DIR}/include)
