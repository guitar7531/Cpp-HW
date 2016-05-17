cmake_minimum_required(VERSION 3.3)
project(ratinal)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp rational.h rational.cpp)
add_executable(rational ${SOURCE_FILES})
add_library(rational STATIC ${SOURSE_LIB})
