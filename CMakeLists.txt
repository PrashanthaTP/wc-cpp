cmake_minimum_required(VERSION 3.30.0)
set(CMAKE_CXX_STANDARD 14)
project(ccwc VERSION 0.1.0)

add_executable(${PROJECT_NAME})
target_sources(${PROJECT_NAME} PRIVATE src/ccwc.cpp)
target_include_directories(${PROJECT_NAME} PRIVATE "include")

