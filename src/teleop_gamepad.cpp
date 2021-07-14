#include <teleop_gamepad.h>

TeleopGamepad::TeleopGamepad(ros::NodeHandle nh, ros::NodeHandle private_nh):
    nh_(nh),
    private_nh_(private_nh)
{
    // Set up subscribers and publishers
    sub_joy_ = nh_.subscribe("/joy", 1, &TeleopGamepad::joyCB, this);
    pub_cmd_vel_ = nh_.advertise<geometry_msgs::Twist>("cmd_vel", 1);

    // Get params
    private_nh_.param<int>("linear_vel_axis", linear_vel_axis_, 1);
    private_nh_.param<int>("angular_vel_axis", angular_vel_axis_, 0);
    private_nh_.param<int>("deadman_switch", deadman_switch_, 5);
    private_nh_.param<int>("turbo_button", turbo_button_, 1);
    private_nh_.param<float>("max_linear_vel", max_linear_vel_, 3);
    private_nh_.param<float>("max_angular_vel", max_angular_vel_, 1);
    private_nh_.param<float>("turbo_max_linear_vel", turbo_max_linear_vel_, 3);
    private_nh_.param<float>("turbo_max_angular_vel", turbo_max_angular_vel_, 1.5);

    // for debugging
    std::cout << "Params:\n" << "* linear_vel_axis: " << linear_vel_axis_ << "\n" << 
        "* angular_vel_axis: " << angular_vel_axis_ <<  "\n" << 
        "* deadman_switch: " << deadman_switch_ <<  "\n" << 
        "* turbo_button: " << turbo_button_ <<  "\n" << 
        "* max_linear_vel: " << max_linear_vel_ <<  "\n" << 
        "* max_angular_vel: " << max_angular_vel_ <<  "\n" << std::endl;

    
}

/*!
   * Takes a joy message and publishes a twist command for the rover
   * @param joy_msg.
   */
void TeleopGamepad::joyCB(const sensor_msgs::Joy::ConstPtr& joy_msg)
{
    bool deadman_pressed = joy_msg->buttons[deadman_switch_];
    bool turbo_button_pressed = joy_msg->buttons[turbo_button_];
    float linear_axis_value = joy_msg->axes[linear_vel_axis_];
    float angular_axis_value = joy_msg->axes[angular_vel_axis_];
    float max_linear_vel = max_linear_vel_;
    float max_angular_vel = max_angular_vel_; 
    if(deadman_pressed)
    {
        if(turbo_button_pressed)
        {
            max_linear_vel = turbo_max_linear_vel_;
            max_angular_vel = turbo_max_angular_vel_;
        }

        geometry_msgs::Twist twist_msg;
        twist_msg.linear.x = linear_axis_value * max_linear_vel;
        twist_msg.angular.z = angular_axis_value * max_angular_vel;

        pub_cmd_vel_.publish(twist_msg);

    }
    else
    {
        geometry_msgs::Twist twist_msg;
        twist_msg.linear.x = 0;
        twist_msg.angular.z = 0;

        pub_cmd_vel_.publish(twist_msg);
    }
}


int main(int argc, char **argv)
{
  ros::init(argc, argv, "teleop_gamepad");
  ros::NodeHandle nh;
  ros::NodeHandle private_nh("~");
  TeleopGamepad teleop_gamepad(nh, private_nh);
  ros::spin();
  return 0;
}