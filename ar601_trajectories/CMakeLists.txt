cmake_minimum_required(VERSION 2.8.3)
project(ar601_trajectories)

find_package(catkin REQUIRED COMPONENTS roscpp std_msgs message_generation roslib)

add_service_files(
  FILES
  GetTrajectory.srv
  )

generate_messages(DEPENDENCIES std_msgs)

catkin_package(
  INCLUDE_DIRS include
  )

include_directories(include ${catkin_INCLUDE_DIRS})

add_executable(ar601_trajectories_node src/service.cpp
  src/f_x.c
  src/f_z.c
  src/main_emxAPI.c
  src/main_trajectory.c
  src/main_emxutil.c
  src/rt_nonfinite.c
  src/rtGetInf.c
  src/rtGetNaN.c
  src/main_data.c
  src/f_zmp_x.c
  )

add_dependencies(ar601_trajectories_node ar601_trajectories_gencpp)

target_link_libraries(ar601_trajectories_node ${catkin_LIBRARIES})
