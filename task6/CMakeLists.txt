cmake_minimum_required(VERSION 3.3)
project(LazyString)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES lazy_string.cpp lazy_string.h)
add_executable(LazyString ${SOURCE_FILES})