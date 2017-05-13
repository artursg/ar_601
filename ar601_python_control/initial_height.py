#!/usr/bin/env python
# license removed for brevity
import rospy
from geometry_msgs.msg import Twist


def set_publishers(pub):
    pub.append(rospy.Publisher('/cog_command', Twist, queue_size=10))
    

def set_initial_angles():
    rate = rospy.Rate(250)
    global pub
    pub=rospy.Publisher('/cog_command', Twist, queue_size=10)
    p = Twist()
    p.angular.x = 0
    p.angular.y = 0
    p.angular.z = 0
    p.linear.y=0
    for i in range(0,1000):
        p.linear.z=0.7615-0.0015*i/1000
	p.linear.x=-0.02
	pub.publish(p)
        rate.sleep()
    for i in range(0,1000):
        p.linear.z=0.76-0.06*i/1000
        p.linear.x=-0.02 + 0.02*i/1000
        pub.publish(p)
        rate.sleep()
    
def tune():
    rospy.init_node('set_height', anonymous=True)
    global pub
    set_initial_angles()




if __name__ == '__main__':
    try:
        tune()      
    except rospy.ROSInterruptException:
        pass
