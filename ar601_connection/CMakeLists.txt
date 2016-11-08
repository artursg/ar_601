cmake_minimum_required(VERSION 2.8.3)
project(ar601_connection)

find_package(catkin REQUIRED COMPONENTS 
  roscpp
  rospy
  roslib
  std_msgs
  sensor_msgs
  kdl_parser
  robot_state_publisher
  ar601_messages
)

catkin_package(
   CATKIN_DEPENDS message_runtime
)

include_directories(include ${catkin_INCLUDE_DIRS})

add_executable(ar601_connection_node src/ar601_connection_node.cpp src/ar_packet.cpp)

target_link_libraries(ar601_connection_node
  ${catkin_LIBRARIES}
   boost_system
   boost_filesystem
 )
