cmake_minimum_required(VERSION 3.16)

project(primes LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)

add_executable(out main.cpp)
target_link_libraries(out pthread)
