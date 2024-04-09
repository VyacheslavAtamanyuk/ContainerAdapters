cmake_minimum_required(VERSION 3.28)
project(labwork9)

set(CMAKE_CXX_STANDARD 20)

add_executable(labwork9 main.cpp)

add_subdirectory(lib)
target_link_libraries(labwork9 my_own_ranges)

add_subdirectory(tests)
enable_testing()
