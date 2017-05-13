#!/usr/bin/env python
# license removed for brevity
import rospy
import sys
from std_msgs.msg import Int8


def set_publishers(pub):
    pub.append(rospy.Publisher('/control/joint_12/state', Int8, queue_size=10))
    pub.append(rospy.Publisher('/control/joint_11/state', Int8, queue_size=10))
    pub.append(rospy.Publisher('/control/joint_10/state', Int8, queue_size=10))
    pub.append(rospy.Publisher('/control/joint_9/state', Int8, queue_size=10))
    pub.append(rospy.Publisher('/control/joint_8/state', Int8, queue_size=10))
    pub.append(rospy.Publisher('/control/joint_7/state', Int8, queue_size= 10))
    pub.append(rospy.Publisher('/control/joint_6/state', Int8, queue_size=10))
    pub.append(rospy.Publisher('/control/joint_5/state', Int8, queue_size=10))
    pub.append(rospy.Publisher('/control/joint_4/state', Int8, queue_size=10))
    pub.append(rospy.Publisher('/control/joint_3/state', Int8, queue_size=10))
    pub.append(rospy.Publisher('/control/joint_2/state', Int8, queue_size=10))
    pub.append(rospy.Publisher('/control/joint_1/state', Int8, queue_size=10))
    

def set_break(pub):
    rate = rospy.Rate(250)
    k=1
    while (k<=1000):
        for i in range(0,12):
            pub[i].publish(0)
        k=k+1
        rate.sleep()
        
    

def f_break():
    rospy.init_node('state', anonymous=True)
    global pub
    pub=[]
    set_publishers(pub)
    set_break(pub)
    
if __name__ == '__main__':
    try:

        f_break()
        
    except rospy.ROSInterruptException:
        pass
