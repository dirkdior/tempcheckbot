#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <stdlib.h>
#include <std_srvs/Empty.h>

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

    //call global_localization service with empty
    // ros::service::waitForService("global_localization");
    // ros::ServiceClient clearClient = node_handle.serviceClient<std_srvs::Empty>("/global_localization");
    // std_srvs::Empty empty_srv;
    // if(clearClient.call(empty_srv)) {
    //     ROS_ERROR("reset global_localization");
    // } else {
    //     ROS_ERROR("Failed to call the global_localization service");
    // }

    while(publisher.getNumSubscribers()==0)
    {
        ROS_ERROR("Waiting for subsribers");
        // system("rosnode kill /map_server"); //kill map_server node
        // system("rosnode kill /amcl"); //kill amcl node
        ros::Duration(3).sleep();
    }

    ROS_ERROR("Got subsriber");

    // Spin the robot for 30 seconds to converge amcl particles
    // moveBot(publisher, 0.01, 0.5);
    // ros::Duration(30).sleep();
    // stopBot(publisher);

    //reset global_localization again
    // if(clearClient.call(empty_srv)) {
    //     ROS_ERROR("reset global_localization");
    // } else {
    //     ROS_ERROR("Failed to call the global_localization service");
    // }

    // Spin the robot for another 60 seconds to converge amcl particles all over again for accuracy
    // moveBot(publisher, 0.01, 0.5);
    // ros::Duration(60).sleep();
    // stopBot(publisher);

    while(ros::ok())
    {
        ros::Duration(3).sleep();    
    }

}