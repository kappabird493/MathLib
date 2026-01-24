cmake_minimum_required(VERSION 3.10)
project(MathLib LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(math INTERFACE)

target_include_directories(math INTERFACE math)

add_executable(example1 example/main.cpp)
add_executable(example2 example/main2.cpp)

target_link_libraries(example1 PRIVATE math)
target_link_libraries(example2 PRIVATE math)
