#include <safety_brake.h>


SafetyBrake::SafetyBrake(ros::NodeHandle nh, ros::NodeHandle private_nh):
    nh_(nh),
    private_nh_(private_nh)
{

    // Set up subscribers and publishers
    sub_SafeCheck_ = nh_.subscribe("cmd_vel_in", 1, &SafetyBrake::checkIfSafe, this);
    sub_Laserscan_ = nh_.subscribe("laserscan", 1, &SafetyBrake::updateCartesianPoints, this);
    pub_cmd_vel_ = nh_.advertise<geometry_msgs::Twist>("cmd_vel_safety_brake", 1);
    pub_status_ = nh_.advertise<std_msgs::Bool>("status", 1);

    // Get params
    private_nh_.param<float>("safety_width", min_width, 1.2);
    private_nh_.param<float>("safety_length", min_length, 1.7);

    // for debugging
    std::cout << "Params:" << std::endl;
    std::cout << "safety_width:" << min_width << std::endl;
    std::cout << "safety_length:" << min_length << std::endl;


    
}

void SafetyBrake::updateCartesianPoints(const sensor_msgs::LaserScan::ConstPtr& laserscan)
{
    // Change polar points into cartesian ones each time the laserscan is published

    float min_angle = laserscan->angle_min, max_angle = laserscan->angle_max;
    float angle_inc = laserscan->angle_increment;

    number_of_points = laserscan->ranges.size();
    data.clear();
    
    // Go through all the points, but only add those who arent inf
    for (int i = 0; i < number_of_points; i++){
        if (!isinf(laserscan->ranges[i])){
            struct point pt;

            pt.angle = min_angle + angle_inc*i;

            pt.x = laserscan->ranges[i]*sin(pt.angle);
            pt.y = laserscan->ranges[i]*cos(pt.angle);
    
            data.push_back(pt);
        }
        
    }

}


void SafetyBrake::checkIfSafe(const geometry_msgs::Twist::ConstPtr& cmd_vel)
{
    float x_thresh = min_width/2;
    float y_thresh = min_length/2;

    status.data = true;
    cmd_vel_safety_break = *cmd_vel;

    //Check for 
    for (const auto& point : data){
        if (abs(point.x) <= x_thresh && abs(point.y) <= y_thresh){
            status.data = false;
            if (cmd_vel->linear.x > 0){ 
                cmd_vel_safety_break.linear.x = 0;
                break;
            }
        }
    }
    
    pub_status_.publish(status);
    pub_cmd_vel_.publish(cmd_vel_safety_break);

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