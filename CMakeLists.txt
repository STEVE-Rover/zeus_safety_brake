cmake_minimum_required(VERSION 3.0.2)
project(zeus_safety_brake)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  sensor_msgs
  std_msgs
  geometry_msgs
)

catkin_package()

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
)

add_executable(safety_brake src/safety_brake.cpp)
target_link_libraries(safety_brake ${catkin_LIBRARIES})
