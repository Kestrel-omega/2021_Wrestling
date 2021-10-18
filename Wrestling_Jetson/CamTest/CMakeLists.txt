cmake_minimum_required(VERSION 3.3)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} [OpenCV.cmake PATH])
project(CamTest)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIR})

set(SOURCE_FILES main.cpp uart.cpp)
add_executable(CamTest ${SOURCE_FILES})
target_link_libraries(CamTest ${OpenCV_LIBRARIES})
