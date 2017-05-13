#!/usr/bin/env python
from math import isnan
import rospy
import message_filters
from std_msgs.msg import Float64
from geometry_msgs.msg import PointStamped
from collections import deque

dx = deque()
dy = deque()
dz = deque()
window = 10

def callback(left,right):
    force=right.point.z+left.point.z
    if force < 2:
        x=0 ##(right.point.x*right.point.z+left.point.x*left.point.z)/(0.001)
        y=0 ##((right.point.y-0.088)*right.point.z+(left.point.y+0.088)*left.point.z)/(0.001)
	force=0
    else:
        x=(right.point.x*right.point.z+left.point.x*left.point.z)/(force)
        y=((right.point.y-0.088)*right.point.z+(left.point.y+0.088)*left.point.z)/(force)
    if isnan(x):
        x = 0
    if isnan(y):
        y = 0
    """
    if x > 0.1:
        x = 0.1
    if x < -0.1:
        x = -0.1
    if y > 0.15:
        y = 0.15
    if y < -0.15:
        y = -0.15    
    """
    dx.append(x)
    dy.append(y)
    dz.append(force)
    dsize = len(dx)
    if dsize > window:
        dx.popleft()
        dy.popleft()
        dz.popleft()
    x = y = z = 0
    for item in dx:
        x = x + item
    for item in dy:
        y = y + item
    for item in dz:
        z = z + item
    dsize = len(dx)
    x = x/dsize
    y = y/dsize
    z = z/dsize
    pub1.publish(x)
    pub2.publish(y)
    pub3.publish(z/9.81)


def converter():
    rospy.init_node('zmp', anonymous=True)
    global pub1, pub2, pub3
    pub1 = rospy.Publisher('/zmp_x', Float64, queue_size=10)
    pub2 = rospy.Publisher('/zmp_y', Float64, queue_size=10)
    pub3 = rospy.Publisher('/weight', Float64, queue_size=10)


    right_sub=message_filters.Subscriber('/force/right_foot_uch_zmp', PointStamped)
    left_sub=message_filters.Subscriber('/force/left_foot_uch_zmp', PointStamped)
    

    ts=message_filters.TimeSynchronizer([left_sub,right_sub],10)
    ts.registerCallback(callback)

    rospy.spin()

if __name__ == '__main__':
    try:
        converter()
    except rospy.ROSInterruptException:
        pass
