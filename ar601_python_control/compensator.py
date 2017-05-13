#!/usr/bin/env python
import rospy

from std_msgs.msg import Float64


def callback(data):
    global pub, initial_angle, x, delta, moment, x_next, moment_prev
    moment=data.data
    if abs(moment-moment_prev)>10:
        moment=moment_prev
    x_next=x+(-3.5563*x+0.0625*moment)*0.004
    delta=-0.0623*x+0.00033345*moment
    pub.publish(initial_angle-delta)
    x=x_next
    moment_prev=moment

    
def compensator():
    rospy.init_node('compensator', anonymous=True)
    global pub, initial_angle, x, delta, moment, x_next, moment_prev
    initial_angle=-8.9
    x=0
    moment_prev=0
    #pub=rospy.Publisher('/control/joint_1/command', Float64, queue_size=10)
    pub=rospy.Publisher('/control/joint_1/command', Float64, queue_size=10)
    rospy.Subscriber("/Mx_right", Float64, callback)

    
    # spin() simply keeps python from exiting until this node is stopped
    rospy.spin()

if __name__ == '__main__':
    try:
        compensator()
    except rospy.ROSInterruptException:
        pass
