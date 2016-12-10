// this program randomly-generated velocity messages for turtlesim
#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <stdlib.h>
#include "std_msgs/String.h"
#include <sstream>
#include <sensor_msgs/PointCloud.h>


using namespace std;
ros::Publisher pub;
ros::Publisher ver;

ros::Publisher dragon;
//ros::Publisher estrellita;

string largo;
string moves="YES", ex="OFF";
int i=0;
float dataxC;

void observo(const std_msgs::String::ConstPtr& msg)
{

//ROS_INFO("I heard: [%s]", msg->data.c_str());
//char a[]=msg->data.c_str();
        largo = msg->data.c_str();



        geometry_msgs::Twist mes;


/*
   if(largo=="veo un color") {

   mes.linear.x=0.5;

   ROS_INFO_STREAM("veo un color");

   }
 */
        if(largo=="no veo un color")
        {
                mes.linear.x= 0.0; mes.angular.z=0.0;
                ROS_INFO_STREAM("no veo camara");
                pub.publish(mes);
                moves="NO";

        }

/*
        if(ex=="ON")
        { moves="NO";
          i++;
          ROS_INFO_STREAM("buscando");
          ROS_INFO_STREAM(i);
          mes.linear.x=0.0;
          mes.angular.z=0.5;
          pub.publish(mes);

          if(i>10)
          {
                  if(largo=="no" || largo=="izquierda" || largo=="derecha" || i>400)
                  {i=0;  moves="YES"; ex="OFF"; }
          }}
 */
        if(moves=="YES")
        {

                mes.linear.x=0.1;
                mes.angular.z=0.0;


                //ROS_INFO_STREAM("estoy viendo");


                if(largo=="obsDERE") { mes.angular.z=-0.5; mes.linear.x= 0.0; ROS_INFO_STREAM("I"); }
                if(largo=="evitarI") { mes.angular.z=0.5; mes.linear.x= 0.0; ROS_INFO_STREAM("D"); }

                if(largo=="izquierda")         //izquierda

                { mes.angular.z = -0.5; mes.linear.x=0.1;   ROS_INFO_STREAM("derecha");  }

                if(largo=="derecha")         //derecha

                { mes.angular.z = 0.5; mes.linear.x=0.1;  ROS_INFO_STREAM("izquierda"); }

                if(largo=="no")
                { mes.angular.z=0.0;  mes.linear.x=0.1; ROS_INFO_STREAM("centro"); }

                pub.publish(mes);
        }


}
void next(const std_msgs::String::ConstPtr& msg)
{

        ex=msg->data.c_str();
        ROS_INFO_STREAM(ex);


}



void sonar_derecho (const sensor_msgs::PointCloud::ConstPtr& msg)
{

        float dataxD=msg->points[0].x;
//ROS_INFO_STREAM("D "<<dataxD);
        geometry_msgs::Twist mv;

        if(dataxD <= 0.4 || dataxC<=15
)
        {
                ROS_INFO_STREAM("esquivar");
                moves="NO";
                mv.angular.z= 0.5;
                mv.linear.x=0.0;


        }

        else
        {

                moves="YES";

                ROS_INFO_STREAM("me muevo");

                mv.linear.x=0.1;
                mv.angular.z=0.0;
        }

        pub.publish(mv);

}
void sonar_izquierdo (const sensor_msgs::PointCloud::ConstPtr& msg)
{

        float dataxI=msg->points[0].x;
        geometry_msgs::Twist mv;
//ROS_INFO_STREAM("I " << dataxI);

        if(dataxI <= 0.4)
        {
                ROS_INFO_STREAM("esquivar");

                moves="NO";
                mv.angular.z= -0.5;
                mv.linear.x=0.0;

        }

        else
        {

                moves="YES";

                ROS_INFO_STREAM("me muevo");

                mv.linear.x=0.1;
                mv.angular.z=0.0;
        }

        pub.publish(mv);


}

void sonar_centro (const sensor_msgs::PointCloud::ConstPtr& msg)
{

        dataxC=msg->points[0].x;
        //ROS_INFO_STREAM(dataxC);

}





int main(int argc, char ** argv) {
        // init ROS
        ros::init(argc, argv, "andreita");
        ros::NodeHandle nh;


        // create a publisher object
        pub = nh.advertise<geometry_msgs::Twist>("/cmd_vel", 1000);
        dragon = nh.advertise<std_msgs::String>("/lleg", 1000);
        //estrellita = nh.advertise<std_msgs::String>("/wander", 1000);


        //crear subscriber
        ros::Subscriber ver = nh.subscribe("/vueltitas", 1000, next);



        ros::Subscriber muevete = nh.subscribe("/semueve", 1000, observo);
        ros::Subscriber obs = nh.subscribe("/esquiva", 1000, observo);
        //ros::Subscriber acc = nh.subscribe("/accion", 1000, ads);
        ros::Subscriber seDe = nh.subscribe("/distance_sensors_state/front_right_srf10", 1000, sonar_derecho);
        ros::Subscriber seId = nh.subscribe("/distance_sensors_state/front_left_srf10", 1000, sonar_izquierdo);
        ros::Subscriber seCe = nh.subscribe("/distance_sensors_state/floor_sensor", 1000, sonar_centro);




/*
   // seed random number generator
   srand(time(0));

   // loop at 2Hz until the node is shutdown
   ros::Rate rate(2);
   while(ros::ok) {
    //  create and fill in the message
    geometry_msgs::Twist msg;


    msg.linear.x= 0.0;
    msg.angular.z = 1.0;



    // publish the message
    pub.publish(msg);

    // send a message to rosout

   ROS_INFO_STREAM(msg.linear.z);

    // wait until its time for another iteration
    ros::spinOnce();
    rate.sleep();

   }
 */
        ros::spin();

        return 0;
}
