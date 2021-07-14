cmake_minimum_required(VERSION 3.0.2)
project(steve_safety_brake)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  sensor_msgs
  std_msgs
  geometry_msgs
  tf2_ros
  pcl_ros
)

find_package(PCL 1.3 REQUIRED COMPONENTS common io)

catkin_package()

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
)

include_directories(${PCL_INCLUDE_DIRS})
link_directories(${PCL_LIBRARY_DIRS})
add_definitions(${PCL_DEFINITIONS})

add_executable(safety_brake src/safety_brake.cpp)
target_link_libraries(safety_brake ${catkin_LIBRARIES})
target_link_libraries(safety_brake ${PCL_LIBRARIES})
