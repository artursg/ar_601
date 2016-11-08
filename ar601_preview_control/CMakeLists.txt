cmake_minimum_required(VERSION 2.8.3)
project(ar601_preview_control)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  roslib
  cmake_modules
  message_filters
  ar601_messages
)

find_package(Eigen REQUIRED)

catkin_package(
  INCLUDE_DIRS include test
  )

include_directories(include test ${EIGEN_INCLUDE_DIRS} ${catkin_INCLUDE_DIRS})
add_definitions(${EIGEN_DEFINITIONS})

add_library(preview_control_lib src/preview_control_node.cpp) 
add_executable(preview_control_node src/main.cpp test/basic_trajectory.cpp)
add_executable(cog_move src/cog_move.cpp)
add_executable(force_node src/force_node.cpp)
#add_executable(zmp_node src/zmp_node.cpp)

target_link_libraries(preview_control_node
  preview_control_lib
  ${catkin_LIBRARIES}
  )

target_link_libraries(cog_move
  ${catkin_LIBRARIES}
  )

target_link_libraries(force_node
  ${catkin_LIBRARIES}
  )

#target_link_libraries(zmp_node
#  ${catkin_LIBRARIES}
#  )

catkin_add_gtest(utest test/utest.cpp test/basic_trajectory.cpp)

target_link_libraries(utest
  preview_control_lib
  ${catkin_LIBRARIES}
  )
