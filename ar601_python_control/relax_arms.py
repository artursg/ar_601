#!/usr/bin/env python
# license removed for brevity
import rospy
import sys
from std_msgs.msg import Int8


def set_publishers(pub):
    pub.append(rospy.Publisher('/control/joint_17/state', Int8, queue_size=10))
    pub.append(rospy.Publisher('/control/joint_18/state', Int8, queue_size=10))
    pub.append(rospy.Publisher('/control/joint_19/state', Int8, queue_size=10))
    pub.append(rospy.Publisher('/control/joint_20/state', Int8, queue_size=10))
    pub.append(rospy.Publisher('/control/joint_21/state', Int8, queue_size=10))
    pub.append(rospy.Publisher('/control/joint_33/state', Int8, queue_size=10))
    pub.append(rospy.Publisher('/control/joint_34/state', Int8, queue_size=10))
    pub.append(rospy.Publisher('/control/joint_35/state', Int8, queue_size=10))
    pub.append(rospy.Publisher('/control/joint_36/state', Int8, queue_size=10))
    pub.append(rospy.Publisher('/control/joint_51/state', Int8, queue_size=10))
    pub.append(rospy.Publisher('/control/joint_49/state', Int8, queue_size=10))
    

def set_relax(pub):
    rate = rospy.Rate(250)
    k=1
    while (k<=1000):
        for i in range(0,11):
            pub[i].publish(2)
        k=k+1
        rate.sleep()

def relax():
    rospy.init_node('state', anonymous=True)
    global pub
    pub=[]
    set_publishers(pub)
    set_relax(pub)
    
if __name__ == '__main__':
    try:

        relax()
        
    except rospy.ROSInterruptException:
        pass
