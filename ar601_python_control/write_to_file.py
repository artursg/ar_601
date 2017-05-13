#!/usr/bin/env python
import rospy
import struct

from std_msgs.msg import Float64


def callback(data):
    global f
    s=str(data.data)
    f.write(s+'\n')
    
def converter():
    rospy.init_node('writer', anonymous=True)
    global f
    f=open('moment_result.txt','w')

    rospy.Subscriber("/Mx_right", Float64, callback)

    
    # spin() simply keeps python from exiting until this node is stopped
    rospy.spin()

if __name__ == '__main__':
    try:
        converter()
    except rospy.ROSInterruptException:
        pass
        f.close()
