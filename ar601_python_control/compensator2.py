#!/usr/bin/env python
import rospy

from std_msgs.msg import Float64


def callback(data):
    global pub, initial_angle, x1, x2, delta, moment, x1_next, x2_next, moment_prev
    moment=data.data
    if abs(moment-moment_prev)>10:
        moment=moment_prev
    x1_next=x1+(3.504*x2+0.125*moment)*0.004
    x2_next=x2+(4*x1)*0.004
    delta=-0.1005*x1-0.06279*x2-0.0005*moment
    pub.publish(initial_angle-delta)
    x1=x1_next
    x2=x2_next
    moment_prev=moment

    
def compensator():
    rospy.init_node('compensator', anonymous=True)
    global pub, initial_angle, x1, x2, delta, moment, x1_next, x2_next, moment_prev
    initial_angle=-8.9
    x1=0
    x2=0
    moment_prev=0
    pub=rospy.Publisher('/compensation', Float64, queue_size=10)
    #pub=rospy.Publisher('/control/joint_1/command', Float64, queue_size=10)
    rospy.Subscriber("/Mx_right", Float64, callback)

    
    # spin() simply keeps python from exiting until this node is stopped
    rospy.spin()

if __name__ == '__main__':
    try:
        compensator()
    except rospy.ROSInterruptException:
        pass
