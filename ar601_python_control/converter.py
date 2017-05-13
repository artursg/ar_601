#!/usr/bin/env python
import rospy

from std_msgs.msg import Float64
from geometry_msgs.msg import PointStamped


def callback1(data):
    pub1.publish(data.point.z/9.81)
    pub2.publish(data.point.x)
    pub3.publish(data.point.y)
def callback2(data):
    pub4.publish(data.point.z/9.81)
    pub5.publish(data.point.x)
    pub6.publish(data.point.y)
    
def converter():
    rospy.init_node('converter', anonymous=True)
    global pub1, pub2, pub3, pub4, pub5, pub6
    pub1 = rospy.Publisher('/weight_right', Float64, queue_size=10)
    pub2 = rospy.Publisher('/Mx_right', Float64, queue_size=10)
    pub3 = rospy.Publisher('/My_right', Float64, queue_size=10)
    pub4 = rospy.Publisher('/weight_left', Float64, queue_size=10)
    pub5 = rospy.Publisher('/Mx_left', Float64, queue_size=10)
    pub6 = rospy.Publisher('/My_left', Float64, queue_size=10)
    rospy.Subscriber("/force/right_foot_uch_moments", PointStamped, callback1)
    rospy.Subscriber("/force/left_foot_uch_moments", PointStamped, callback2)
    
    # spin() simply keeps python from exiting until this node is stopped
    rospy.spin()

if __name__ == '__main__':
    try:
        converter()
    except rospy.ROSInterruptException:
        pass
