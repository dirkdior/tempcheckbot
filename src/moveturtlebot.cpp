#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <stdlib.h>

void stopBot(ros::Publisher publisher) {
    geometry_msgs::Twist msg;

    msg.linear.x  = 0.0;
    msg.angular.z = 0.0;

    publisher.publish(msg);
    ros::spinOnce();
}

void moveBot(ros::Publisher publisher, double linX, double angZ) {
    geometry_msgs::Twist msg;

    msg.linear.x  = linX;
    msg.angular.z = angZ;

    publisher.publish(msg);
    ros::spinOnce();
}

int main(int argc, char** argv)
{
    ros::init(argc, argv, "moveturtlebot");

    ros::NodeHandle node_handle;

    ros::Publisher publisher = node_handle.advertise<geometry_msgs::Twist>("/cmd_vel", 20, true);

    // double linX = 0.1;
    // double angZ = 0.0;

    // ros::Rate rate(10);
    // while(ros::ok())
    // {
    //     geometry_msgs::Twist msg;
        
    //     msg.linear.x  = linX;
    //     msg.angular.z = angZ;

    //     publisher.publish(msg);
    //     ros::spinOnce();
    //     rate.sleep();
    // }

    while(publisher.getNumSubscribers()==0)
    {
        ROS_ERROR("Waiting for subsribers");
        ros::Duration(3).sleep();
    }

    ROS_ERROR("Got subsriber");

    moveBot(publisher, 0.3, 0.0);
    ros::Duration(12).sleep();
    stopBot(publisher);
    ros::Duration(1).sleep();
    moveBot(publisher, 0.0, 0.29);
    ros::Duration(6).sleep();
    stopBot(publisher);
    ros::Duration(1).sleep();
    moveBot(publisher, 0.3, 0.0);
    ros::Duration(4).sleep();
    stopBot(publisher);
    ros::Duration(1).sleep();
    moveBot(publisher, 0.0, -0.29);
    ros::Duration(7).sleep();
    stopBot(publisher);
    ros::Duration(1).sleep();
    moveBot(publisher, -0.3, 0.0);
    ros::Duration(11).sleep();
    stopBot(publisher);

    while(ros::ok())
    {
        ros::Duration(3).sleep();    
    }

}