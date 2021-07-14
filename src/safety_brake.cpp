#include <safety_brake.h>

SafetyBrake::SafetyBrake(ros::NodeHandle nh, ros::NodeHandle private_nh):
    nh_(nh),
    private_nh_(private_nh)
{

    // Set up subscribers and publishers
    sub_PointCloud_ = nh_.subscribe("/cloud_in", 1, &SafetyBrake::changeFrame, this);
    pub_cmd_vel_ = nh_.advertise<geometry_msgs::Twist>("cmd_vel", 1);
    pub_test = nh_.advertise<sensor_msgs::PointCloud2>("test", 1);

    // Initialize transformer
    tf_listener = new tf2_ros::TransformListener(tfBuffer);

    // for debugging
    std::cout << "Params:" << std::endl;
    
}


void SafetyBrake::changeFrame(const sensor_msgs::PointCloud2::ConstPtr& cloud_in)
{
    sensor_msgs::PointCloud2 cloud_out;

    geometry_msgs::TransformStamped transformStamped;
    try {
        
        transformStamped = tfBuffer.lookupTransform(
            "base_link", "d435_depth_optical_frame", ros::Time(0));

        // Debugging
        std::cout << "******************" << std::endl;
        std::cout << transformStamped << std::endl;

        Eigen::Matrix4f mat = tf2::transformToEigen(transformStamped.transform).matrix().cast<float>();

        pcl_ros::transformPointCloud(mat, *cloud_in, cloud_out);

    } catch (tf2::TransformException &ex) {
        ROS_WARN("%s", ex.what());
        ros::Duration(1.0).sleep();
    }

    pub_test.publish(cloud_out);

}


int main(int argc, char **argv)
{
  ros::init(argc, argv, "teleop_gamepad");
  ros::NodeHandle nh;
  ros::NodeHandle private_nh("~");
  SafetyBrake safety_brake(nh, private_nh);
  ros::spin();
  return 0;
}