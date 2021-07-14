#ifndef SAFETY_BRAKE_H
#define SAFETY_BRAKE_H

#include <iostream>
#include <ros/ros.h>
#include <sensor_msgs/Joy.h>
#include <geometry_msgs/Twist.h>

class TeleopGamepad
{
    public:
        TeleopGamepad(ros::NodeHandle nh, ros::NodeHandle private_nh);

    private:
        void joyCB(const sensor_msgs::Joy::ConstPtr& joy_msg);

        // ROS variables
        ros::NodeHandle nh_;
        ros::NodeHandle private_nh_;
        ros::Subscriber sub_joy_;
        ros::Publisher pub_cmd_vel_;

        // Parameters
        int linear_vel_axis_;
        int angular_vel_axis_;
        int deadman_switch_;
        int turbo_button_;
        float max_linear_vel_;
        float max_angular_vel_;
        float turbo_max_linear_vel_;
        float turbo_max_angular_vel_;
};


#endif