#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>

typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

void moveBot(double goalPosX, double goalOrntW) {

    MoveBaseClient ac("move_base", true);

    while(!ac.waitForServer(ros::Duration(5.0))){
        ROS_INFO("Waiting for the move_base action server to come up");
    }

    move_base_msgs::MoveBaseGoal goal;

    goal.target_pose.header.frame_id = "base_link";
    goal.target_pose.header.stamp = ros::Time::now();

    goal.target_pose.pose.position.x = goalPosX;
    goal.target_pose.pose.orientation.w = goalOrntW;

    ROS_INFO("Sending goal");
    ac.sendGoal(goal);

    ac.waitForResult();
   
    if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
        ROS_INFO("Hooray, the base moved 1 meter forward");
    else
        ROS_INFO("The base failed to move forward 1 meter for some reason");
}

int main(int argc, char** argv) {
    ros::init(argc, argv, "moveturtlebot");
    
    moveBot(
        5.0,
        2.0
    );
    ros::Duration(30).sleep();
    moveBot(
        1.0,
        6.0
    );
    ros::Duration(30).sleep();
    
    moveBot(
        3.0,
        6.0
    );

    return 0;
}