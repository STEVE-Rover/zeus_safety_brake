#ifndef SAFETY_BRAKE_H
#define SAFETY_BRAKE_H

#include <iostream>
#include <ros/ros.h>

#include <geometry_msgs/Twist.h>
#include <sensor_msgs/LaserScan.h>


class SafetyBrake
{
    public:
        SafetyBrake(ros::NodeHandle nh, ros::NodeHandle private_nh);

    private:
        void polar2cartesian(const sensor_msgs::LaserScan::ConstPtr& cloud_in);



        // ROS variables
        ros::NodeHandle nh_;
        ros::NodeHandle private_nh_;
        ros::Subscriber sub_PointCloud_;
        ros::Publisher pub_cmd_vel_;
        ros::Publisher pub_test;

        // Parameters
        tf2_ros::Buffer tfBuffer;
        tf2_ros::TransformListener* tf_listener;

       
};


#endif