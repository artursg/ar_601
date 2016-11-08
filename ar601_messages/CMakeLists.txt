cmake_minimum_required(VERSION 2.8.3)
project(ar601_messages)

find_package(catkin REQUIRED COMPONENTS std_msgs sensor_msgs message_generation)

## Generate messages in the 'msg' folder
add_message_files(
  FILES
  JointStatus.msg
  Power.msg
)

## Generate services in the 'srv' folder
add_service_files(
  FILES
  FK.srv
  IK.srv
)

generate_messages(
  DEPENDENCIES geometry_msgs
  std_msgs
  sensor_msgs

)


catkin_package(
    CATKIN_DEPENDS sensor_msgs std_msgs  message_runtime
)
