#include <safety_brake.h>


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

    float min_angle = laserscan->angle_min, max_angle = laserscan->angle_max;
    float angle_inc = laserscan->angle_increment;

    number_of_points = laserscan->ranges.size();
    
    for (int i = 0; i < number_of_points; i++){
        float angle = min_angle + angle_inc*i;
        std::cout << angle << std::endl;

        struct point pt;
        pt.x = laserscan->ranges[i]*sin(angle);
        pt.y = laserscan->ranges[i]*cos(angle);
        std::cout << "pt.x: " << pt.x << std::endl;
        std::cout << "pt.y: " << pt.y << std::endl;
    }

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