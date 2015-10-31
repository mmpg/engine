cmake_minimum_required(VERSION 2.8)
project(engine)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES src/main.cpp)
add_executable(engine ${SOURCE_FILES})
