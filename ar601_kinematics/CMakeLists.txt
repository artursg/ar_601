cmake_minimum_required(VERSION 2.8.3)
project(ar601_kinematics)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  std_msgs
  ar601_messages
)

catkin_package(
  INCLUDE_DIRS include
)

include_directories(include ${catkin_INCLUDE_DIRS})

add_executable(ar601_ikinematics_node src/iservice.cpp
  src/ik_left.c
  src/ik_left_12.c
  src/ik_left_initialize.c
  src/ik_left_rtwutil.c
  src/ik_left_terminate.c
  src/ik_right.c
  src/ik_right_12.c
  src/q4.c
  src/q5_1.c
  src/q5_2.c
  src/q5_3.c
  src/q5_4.c
  src/rtGetInf.c
  src/rtGetNaN.c
  src/rt_nonfinite.c
  src/T46.c
  src/inv.c
  src/mpower.c
  )

add_executable(ar601_fkinematics_node src/fservice.cpp
  src/left_in_right.c
  src/right_in_left.c
  src/rdivide.c
  )

target_link_libraries(ar601_ikinematics_node ${catkin_LIBRARIES})
target_link_libraries(ar601_fkinematics_node ${catkin_LIBRARIES})
