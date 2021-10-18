cmake_minimum_required(VERSION 3.3)
project(UARTTest)

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

set(SOURCE_FILES main.cpp uart.cpp)
add_executable(UARTTest ${SOURCE_FILES})
target_link_libraries(UARTTest ${OpenCV_LIBRARIES})