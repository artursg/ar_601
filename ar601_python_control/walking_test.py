#!/usr/bin/env python
# license removed for brevity
import rospy
import sys
import dynamic_reconfigure.client
from gazebo_msgs.msg import LinkStates
from std_msgs.msg import Float64
import std_srvs.srv
import numpy as np
import time

from sensor_msgs.msg import JointState


def set_publishers(pub):
    pub.append(rospy.Publisher('/control/joint_12/command', Float64, queue_size=10))
    pub.append(rospy.Publisher('/control/joint_11/command', Float64, queue_size=10))
    pub.append(rospy.Publisher('/control/joint_10/command', Float64, queue_size=10))
    pub.append(rospy.Publisher('/control/joint_9/command', Float64, queue_size=10))
    pub.append(rospy.Publisher('/control/joint_8/command', Float64, queue_size=10))
    pub.append(rospy.Publisher('/control/joint_7/command', Float64, queue_size= 10))
    pub.append(rospy.Publisher('/control/joint_6/command', Float64, queue_size=10))
    pub.append(rospy.Publisher('/control/joint_5/command', Float64, queue_size=10))
    pub.append(rospy.Publisher('/control/joint_4/command', Float64, queue_size=10))
    pub.append(rospy.Publisher('/control/joint_3/command', Float64, queue_size=10))
    pub.append(rospy.Publisher('/control/joint_2/command', Float64, queue_size=10))
    pub.append(rospy.Publisher('/control/joint_1/command', Float64, queue_size=10))
    

def set_initial_angles(pub,input_angles):
    rate = rospy.Rate(250)
    for i in range(1,2000):
        pub[0].publish(input_angles[0]*i/2000)
        pub[1].publish(input_angles[1]*i/2000)
        pub[2].publish(input_angles[2]*i/2000)
        pub[3].publish(input_angles[3]*i/2000)
        pub[4].publish(input_angles[4]*i/2000) 
        pub[5].publish(input_angles[5]*i/2000)
        pub[6].publish(input_angles[6]*i/2000)
        pub[7].publish(input_angles[7]*i/2000)
        pub[8].publish(input_angles[8]*i/2000)
        pub[9].publish(input_angles[9]*i/2000)
        pub[10].publish(input_angles[10]*i/2000)
        pub[11].publish(input_angles[11]*i/2000)
	print input_angles[3]*i/2000
        rate.sleep()
    

def set_angles(pub,input_angles):
    rate = rospy.Rate(250)
    i=0
    while (rospy.is_shutdown()!=1):
        if i>10000:
            i=7500 
        pub[0].publish(input_angles[i,0])
        pub[1].publish(input_angles[i,1])
        pub[2].publish(input_angles[i,2])
        pub[3].publish(input_angles[i,3])
        pub[4].publish(input_angles[i,4]) 
        pub[5].publish(input_angles[i,5])
        pub[6].publish(input_angles[i,6])
        pub[7].publish(input_angles[i,7])
        pub[8].publish(input_angles[i,8])
        pub[9].publish(input_angles[i,9])
        pub[10].publish(input_angles[i,10])
        pub[11].publish(input_angles[i,11])
        print input_angles[i,3]
        i=i+1
        rate.sleep()


def tune():
    rospy.init_node('walking_test', anonymous=True)
    global array
    array=np.load('~/catkin_ws/src/ar_601/ar601_python_control/angles.npy')
    global pub
    pub=[]
    set_publishers(pub)
    #set_initial_angles(pub,array[0,:])
    time.sleep(3)
    set_angles(pub,array) 



if __name__ == '__main__':
    try:

        tune()
        
    except rospy.ROSInterruptException:
        pass
