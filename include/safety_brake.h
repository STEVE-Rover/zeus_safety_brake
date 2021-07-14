#ifndef SAFETY_BRAKE_H
#define SAFETY_BRAKE_H

#include <iostream>
#include <ros/ros.h>

#include <pcl_ros/transforms.h>
#include <tf2_ros/transform_listener.h>
#include <tf2_ros/buffer.h>

#include <geometry_msgs/Twist.h>
#include <sensor_msgs/PointCloud2.h>

//#include <tf2_geometry_msgs/tf2_geometry_msgs.h>
//#include <tf2_sensor_msgs/tf2_sensor_msgs.h>
#include <tf2/transform_datatypes.h>
#include <tf2_eigen/tf2_eigen.h>


class SafetyBrake
{
    public:
        SafetyBrake(ros::NodeHandle nh, ros::NodeHandle private_nh);

    private:
        void changeFrame(const sensor_msgs::PointCloud2::ConstPtr& cloud_in);



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