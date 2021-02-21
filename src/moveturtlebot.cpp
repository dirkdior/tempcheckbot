#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <stdlib.h>

int main(int argc, char** argv)
{
    ros::init(argc, argv, "moveturtlebot");

    ros::NodeHandle node_handle;

    ros::Publisher publisher = node_handle.advertise<geometry_msgs::Twist>("/cmd_vel", 1000);

    srand(time(0));

    double linX = 2.0;
    double angZ = 0.0;

    ros::Rate rate(10);
    while(ros::ok())
    {
        geometry_msgs::Twist msg;
        
        msg.linear.x  = linX;
        msg.angular.z = angZ;

        publisher.publish(msg);
        ros::spinOnce();
        rate.sleep();
    }

}