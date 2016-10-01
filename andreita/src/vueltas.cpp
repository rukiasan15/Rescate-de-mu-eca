// this program randomly-generated velocity messages for turtlesim
#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <stdlib.h>
#include "std_msgs/String.h"
#include <sstream>


ros::Publisher pub;


void gira(const std_msgs::String::ConstPtr& msg)
   {
//ROS_INFO_STREAM(msg->data.c_str());

int largo = strlen(msg->data.c_str());
		

geometry_msgs::Twist ho;

if(largo==2)
{ ho.angular.z=0.0; }

	if(largo==9)

{ ho.angular.z =-0.1;	}

if(largo==7)

{		ho.angular.z = 0.1;	}
	


		pub.publish(ho);

ROS_INFO_STREAM(ho.angular.z);
	

		// wait until its time for another iteration


}
 
int main(int argc, char ** argv) {
	// init ROS
	ros::init(argc, argv, "vueltas");
	ros::NodeHandle nh;


	// create a publisher object
pub = nh.advertise<geometry_msgs::Twist>("/cmd_vel", 1000);


	//crear subscriber
	
ros::Subscriber girar = nh.subscribe("/semueve", 1000, gira);

	

	
ros::spin();
return 0;
}
