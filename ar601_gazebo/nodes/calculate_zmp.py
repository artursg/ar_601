#!/usr/bin/env python
import rospy
import message_filters
from geometry_msgs.msg import WrenchStamped, PointStamped
from std_msgs.msg import Header
from gazebo_msgs.msg import ContactState

pub = rospy.Publisher('zmp_point', PointStamped, queue_size=10)

def publish_left(contacts):
    print 'd'
    forces = contacts.wrenches
    for point in forces:
        print point.force

def publish_right(contacts):
    print 'z'
    forces = contacts.wrenches

    
def callback(right, left):
    rzmp_z = right.wrench.force.z
    rzmp_x = right.wrench.torque.x / rzmp_z
    rzmp_y = right.wrench.torque.y / rzmp_z
    lzmp_z = left.wrench.force.z
    lzmp_x = left.wrench.torque.x / lzmp_z
    lzmp_y = left.wrench.torque.y / lzmp_z
    zmp_x = (rzmp_z*rzmp_x + lzmp_z*lzmp_x)/(rzmp_z + lzmp_z)
    zmp_y = (rzmp_z*rzmp_y + lzmp_z*lzmp_y)/(rzmp_z + lzmp_z)
    zmp_z = 0
    p = PointStamped()
    p.header = Header()
    p.header.frame_id = "head"
    p.point.x = zmp_x
    p.point.y = zmp_y
    p.point.z = zmp_z    
    pub.publish(p)
    
if __name__ == '__main__':
    rospy.init_node('zmp_node');
    rospy.Subscriber('stopa_p_state', ContactState, publish_right)
    rospy.Subscriber('stopa_l_state', ContactState, publish_left)    
    rospy.spin()
