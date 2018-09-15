cmake_minimum_required(VERSION 2.8.3) # my ubuntu 16.04, cmake 3.5.1
project(systrace)

set(CMAKE_BUILD_TYPE "Release")
set(CMAKE_CXX_FLAGS "-std=c++11")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -Wall -g")
set(USE_ROS true)

if(USE_ROS)
find_package(catkin REQUIRED COMPONENTS
roscpp
roslib
)
catkin_package(
INCLUDE_DIRS src
LIBRARIES ${PROJECT_NAME}
#CATKIN_DEPENDS
#DEPENDS
)
endif()

add_library(${PROJECT_NAME}
src/tracer.cpp
)
