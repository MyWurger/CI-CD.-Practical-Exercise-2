cmake_minimum_required(VERSION 3.16)
project(calculator CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(calc_lib src/calc.cpp)
target_include_directories(calc_lib PUBLIC src)

add_executable(calc_app src/main.cpp)
target_link_libraries(calc_app PRIVATE calc_lib)
