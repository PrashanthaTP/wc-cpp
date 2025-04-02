cmake_minimum_required(VERSION 3.30.0)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(ccwc VERSION 0.1.0)

set(PRJ_LIB_NAME ccwc_lib)
add_library(${PRJ_LIB_NAME} STATIC src/ccwc.cpp)
target_include_directories(${PRJ_LIB_NAME} PUBLIC "include")

add_executable(${PROJECT_NAME})
target_sources(${PROJECT_NAME} PRIVATE src/main.cpp)
# target_include_directories(${PROJECT_NAME} PRIVATE "include")
target_link_libraries(${PROJECT_NAME} PRIVATE ${PRJ_LIB_NAME})

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
include(GtestSetup)
add_subdirectory(test)
