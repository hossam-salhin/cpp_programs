cmake_minimum_required(VERSION 3.10)

project(RobotTracker)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

add_executable(robot_tracker
src/main.cpp
src/simulator.cpp
src/logger.cpp
src/robot.cpp
)

