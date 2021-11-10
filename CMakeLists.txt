cmake_minimum_required(VERSION 3.16)

project(primes VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)

option(USE_SHARED_LIB "Used shared library vs static library" ON)

if(USE_SHARED_LIB)
  add_library(${PROJECT_NAME} SHARED src/primes.cpp)
else()
  add_library(${PROJECT_NAME} STATIC src/primes.cpp)
endif()

add_executable(out src/main.cpp)

target_include_directories(out PUBLIC ${CMAKE_SOURCE_DIR}/include/)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/include/)

target_link_libraries(out PRIVATE pthread ${PROJECT_NAME})
target_link_libraries(${PROJECT_NAME} INTERFACE pthread)

