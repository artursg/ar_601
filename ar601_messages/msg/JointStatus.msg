# Joint motor status
std_msgs/Int64[] voltage  # voltage
std_msgs/Int64[] load 	  # load 
std_msgs/Int64[] kp	  # proportional coefficient
std_msgs/Int64[] ki	  # intergral coefficent
std_msgs/Float64[] maximum # maximum position of joint
std_msgs/Float64[] minimum # minimum position of joint 
std_msgs/Bool[] over_maximum # is joint location is over maximum 
std_msgs/Bool[] over_minimum # is joint location is over minimum
std_msgs/Int8[] status	  # joint status - 0 - brake, 1 - relax, 2 - unbrake, 3 - trace 
std_msgs/Bool[] torque_control # is joint torque controlled 