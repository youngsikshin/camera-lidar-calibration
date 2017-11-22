cmake_minimum_required(VERSION 2.8.3)
project(camera_lidar_calibration)

add_definitions(-std=c++11)

# Find includes in corresponding build directories
# Adds in each directory ${CMAKE_CURRENT_SOURCE_DIR} and ${CMAKE_CURRENT_BINARY_DIR}
# set(CMAKE_INCLUDE_CURRENT_DIR ON)
set (SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

set (SRC
    src/main.cpp
)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

find_package (Ceres REQUIRED)

find_package(catkin REQUIRED COMPONENTS
    roscpp
    std_msgs
    geometry_msgs
    message_generation
)

catkin_package(
    INCLUDE_DIRS include
    CATKIN_DEPENDS
      roscpp
      std_msgs
      geometry_msgs
)

include_directories(
    include
    ${catkin_INCLUDE_DIRS}
    ${CMAKE_CURRENT_BINARY_DIR}
    ${CERES_INCLUDE_DIRS}
)

add_executable (camera_lidar_calibration ${SRC})
target_link_libraries (camera_lidar_calibration
    ${CERES_LIBRARIES}
)
