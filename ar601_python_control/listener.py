#!/usr/bin/env python
import rospy

from std_msgs.msg import Float64


def callback(data):
    global maximum
    q=abs(data.data)
    if q>maximum:
        maximum=q
        print maximum
    
def converter():
    rospy.init_node('converter', anonymous=True)
    global maximum
    maximum=0
    rospy.Subscriber("/y_controller", Float64, callback)
    
    # spin() simply keeps python from exiting until this node is stopped
    rospy.spin()

if __name__ == '__main__':
    try:
        converter()
    except rospy.ROSInterruptException:
        pass
