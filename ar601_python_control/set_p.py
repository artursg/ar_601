#!/usr/bin/env python
# license removed for brevity
import rospy
import sys
from std_msgs.msg import Int64


def set_publishers(pub):
    pub.append(rospy.Publisher('/control/joint_12/p', Int64, queue_size=10))
    pub.append(rospy.Publisher('/control/joint_11/p', Int64, queue_size=10))
    pub.append(rospy.Publisher('/control/joint_10/p', Int64, queue_size=10))
    pub.append(rospy.Publisher('/control/joint_9/p', Int64, queue_size=10))
    pub.append(rospy.Publisher('/control/joint_8/p', Int64, queue_size=10))
    pub.append(rospy.Publisher('/control/joint_7/p', Int64, queue_size= 10))
    pub.append(rospy.Publisher('/control/joint_6/p', Int64, queue_size=10))
    pub.append(rospy.Publisher('/control/joint_5/p', Int64, queue_size=10))
    pub.append(rospy.Publisher('/control/joint_4/p', Int64, queue_size=10))
    pub.append(rospy.Publisher('/control/joint_3/p', Int64, queue_size=10))
    pub.append(rospy.Publisher('/control/joint_2/p', Int64, queue_size=10))
    pub.append(rospy.Publisher('/control/joint_1/p', Int64, queue_size=10))
    

def set_p(pub,p):
    rate = rospy.Rate(250)
    k=1
    while (k<=250):
        for i in range(0,12):
            pub[i].publish(p)
        k=k+1
        rate.sleep()
    

def main(p):
    rospy.init_node('state', anonymous=True)
    global pub
    pub=[]
    set_publishers(pub)
    set_p(pub,p)
    
if __name__ == '__main__':
    try:

        main(int(sys.argv[1]))
        
    except rospy.ROSInterruptException:
        pass
