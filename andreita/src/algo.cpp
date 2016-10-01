#include "ros/ros.h"
#include "std_msgs/String.h"
#include <sensor_msgs/PointCloud.h>
#include "ArExport.h"
#include "Aria.h"

using namespace std;



void wandering(const std_msgs::String::ConstPtr& msg)
{

string permiso=msg->data.c_str();

if(permiso==1) {ArModeWander wander(&robot, "wander", 'w', 'W'); }

else if (permiso==0)

 { ArModeTeleop teleop(&robot, "teleop", 't', 'T'); }

}


int main(int argc, char **argv)
{
  
  ros::init(argc, argv, "sonar");

  ros::NodeHandle n;

  
  ros::Subscriber ian = n.subscribe("/wander", 1000, wandering);


ros::spin();


  return 0;


}
