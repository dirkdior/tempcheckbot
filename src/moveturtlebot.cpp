#include <ros/ros.h>
#include <std_msgs/String.h>
#include <sstream>
#include <move_base_msgs/MoveBaseAction.h>
#include <gazebo_msgs/GetModelState.h>
#include <actionlib/client/simple_action_client.h>

typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

void moveBot(double goalPosX, double goalPosY, double goalPosZ, double goalOrntW) {

    MoveBaseClient ac("move_base", true);

    while(!ac.waitForServer(ros::Duration(5.0))){
        ROS_INFO("Waiting for the move_base action server to come up");
    }

    move_base_msgs::MoveBaseGoal goal;

    goal.target_pose.header.frame_id = "base_link";
    goal.target_pose.header.stamp = ros::Time::now();

    goal.target_pose.pose.position.x = goalPosX;
    goal.target_pose.pose.position.y = goalPosY;
    goal.target_pose.pose.position.z = goalPosZ;
    goal.target_pose.pose.orientation.w = goalOrntW;

    ROS_INFO("Sending goal");
    ac.sendGoal(goal);

    ac.waitForResult();
   
    if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
        ROS_INFO("Hooray, the base moved 1 meter forward");
    else
        ROS_INFO("The base failed to move forward 1 meter for some reason");
}

void moveBotFull(double goalPosX, double goalPosY, double goalPosZ, double goalOrntX, double goalOrntY, double goalOrntZ, double goalOrntW) {

    MoveBaseClient ac("move_base", true);

    while(!ac.waitForServer(ros::Duration(5.0))){
        ROS_INFO("Waiting for the move_base action server to come up");
    }

    move_base_msgs::MoveBaseGoal goal;

    goal.target_pose.header.frame_id = "base_link";
    goal.target_pose.header.stamp = ros::Time::now();

    goal.target_pose.pose.position.x = goalPosX;
    goal.target_pose.pose.position.y = goalPosY;
    goal.target_pose.pose.position.z = goalPosZ;
    goal.target_pose.pose.orientation.x = goalOrntX;
    goal.target_pose.pose.orientation.y = goalOrntY;
    goal.target_pose.pose.orientation.z = goalOrntZ;
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
    ros::NodeHandle n;
    gazebo_msgs::GetModelState gms;
    ros::ServiceClient svc = n.serviceClient<gazebo_msgs::GetModelState>("/gazebo/get_model_state");
    gms.request.model_name = "person_standing";
    svc.call(gms);
    
    ROS_WARN_STREAM("Received from model: \n" << gms.response);

    moveBotFull(
        gms.response.pose.position.x - 0.5,
        gms.response.pose.position.y,
        gms.response.pose.position.z,
        gms.response.pose.orientation.x,
        gms.response.pose.orientation.y,
        gms.response.pose.orientation.z,
        gms.response.pose.orientation.w
    );

    ros::Publisher cmd_vel_pub_;
    cmd_vel_pub_ = n.advertise<geometry_msgs::Twist>("cmd_vel", 1);

    geometry_msgs::Twist msg;
    msg.angular.y = 1.0;

    // ros::Duration(60).sleep();

    cmd_vel_pub_.publish(msg);

    // ros::Duration(60).sleep();

    gms.request.model_name = "person_standing_0";
    svc.call(gms);
    ROS_WARN_STREAM("Received from model: \n" << gms.response);

    moveBotFull(
        gms.response.pose.position.x - 0.5,
        gms.response.pose.position.y,
        gms.response.pose.position.z,
        gms.response.pose.orientation.x,
        gms.response.pose.orientation.y,
        gms.response.pose.orientation.z,
        gms.response.pose.orientation.w
    );

    // ros::Duration(60).sleep();

    cmd_vel_pub_.publish(msg);

    // ros::Duration(60).sleep();

    gms.request.model_name = "person_standing_1";
    svc.call(gms);
    ROS_WARN_STREAM("Received from model: \n" << gms.response);

    moveBotFull(
        gms.response.pose.position.x - 0.5,
        gms.response.pose.position.y,
        gms.response.pose.position.z,
        gms.response.pose.orientation.x,
        gms.response.pose.orientation.y,
        gms.response.pose.orientation.z,
        gms.response.pose.orientation.w
    );

    // ros::Duration(60).sleep();

    cmd_vel_pub_.publish(msg);

    // moveBot(
    //     0.5,
    //     -1.6,
    //     0.0,
    //     1.0
    // );
    // ros::Duration(30).sleep();
    // moveBot(
    //     1.0,
    //     6.0
    // );
    // ros::Duration(30).sleep();
    
    // moveBot(
    //     3.0,
    //     6.0
    // );

    return 0;
}