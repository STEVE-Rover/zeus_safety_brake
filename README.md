# steve_safety_brake
This package is for stopping the rover if an object is detected too close.

## How does it works
This package uses the Laserscan data produced by obstacle_detector_PC_to_LS and converts it into cartesian coordinates. When a cmd_vel is published, it then looks to see if a point is inside the safety zone and proceeds to stop the rover from positive linear x speed if it detects one.

### Subscribed topics
* cmd_vel_watchdog (geometry_msgs/Twist): Velocity cmd from watchdog.
### Published topics
* cmd_vel_out (geometry_msgs/Twist): output velocity command for the mobile base.

### Parameters
* ~safety_width (float, default: 1.2): Width of the safety zone where if a point is detected it will stop the rover from moving forward.
* ~safety_length (float, default: 1.7): Length of the safety zone where if a point is detected it will stop the rover from moving forward.
