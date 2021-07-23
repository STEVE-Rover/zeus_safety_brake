#include <safety_brake.h>

#include <typeinfo>

SafetyBrake::SafetyBrake(ros::NodeHandle nh, ros::NodeHandle private_nh):
    nh_(nh),
    private_nh_(private_nh)
{

    // Set up subscribers and publishers
    sub_SafeCheck_ = nh_.subscribe("cmd_vel_in", 1, &SafetyBrake::checkIfSafe, this);
    sub_Laserscan_ = nh_.subscribe("laserscan", 1, &SafetyBrake::polar2cartesian, this);
    pub_cmd_vel_ = nh_.advertise<geometry_msgs::Twist>("cmd_vel_safety_brake", 1);


    // for debugging
    std::cout << "Params:" << std::endl;
    
}

void SafetyBrake::polar2cartesian(const sensor_msgs::LaserScan::ConstPtr& laserscan)
{
    std::cout << "Debug :" << std::endl;
    std::cout << typeid(laserscan).name() << std::endl;
    std::cout << typeid(*laserscan).name() << std::endl; //this is the real value

    float min_angle, max_angle;
    float angle_inc;

    number_of_points = sizeof(laserscan->ranges)/sizeof(laserscan->ranges[0]);
    std::cout << number_of_points << std::endl;
}


void SafetyBrake::checkIfSafe(const geometry_msgs::Twist::ConstPtr& cmd_vel)
{
    

    pub_cmd_vel_.publish(cmd_vel);

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