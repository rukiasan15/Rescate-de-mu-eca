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

        if(ex=="ON")
        { moves="NO";
          i++;
          ROS_INFO_STREAM("buscando");
          ROS_INFO_STREAM(i);

          mes.linear.x=0.0;
          mes.angular.z=0.5;
          pub.publish(mes);

          if(i>20)
          {
                  if(largo=="no" || largo=="izquierda" || largo=="derecha" || i>20000)
                  {i=0;  moves="YES"; ex="OFF"; }
          }}

        if(moves=="YES" && ex=="OFF")
        {

                mes.linear.x=0.1;
                mes.angular.z=0.0;
                pub.publish(mes);


                if(largo=="obsDERE") { mes.angular.z=0.5; mes.linear.x= 0.0; //moverse a izquierda
                }
                if(largo=="evitarI") { mes.angular.z=-0.5; mes.linear.x= 0.0; //moverse a derecha
                }

                if(largo=="izquierda")         //izquierda

                { mes.angular.z =-0.5; mes.linear.x=0.1;   ROS_INFO_STREAM("izquierda");  }

                if(largo=="derecha")         //derecha

                { mes.angular.z =0.5; mes.linear.x=0.1;  ROS_INFO_STREAM("derecha"); }

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
void hola(const sensor_msgs::PointCloud::ConstPtr& msg)
{


        geometry_msgs::Twist mv;

        std_msgs::String st;
        std::stringstream sp;

        if(ex=="OFF")
        {
                float datax1=msg->points[1].x;
                float datax2=msg->points[2].x;
                float datax3=msg->points[3].x;
                float datax4=msg->points[4].x;
                float datax5=msg->points[5].x;
                float datax6=msg->points[6].x;



                if(datax1<0.38 && datax2<0.38 && datax3<0.38 && datax4<0.38 && datax5<0.38 && datax6<0.38)
                {

                        moves="NO";

                        ROS_INFO_STREAM("GO SONAR");
                        mv.angular.z= -0.5;
                        mv.linear.x=0.0;
                        pub.publish(mv);

                }


                if(datax1<0.38 || datax2<0.38 || datax3<0.38)                         //derecha
                {
                        moves="NO";

                        ROS_INFO_STREAM("GO SONAR");
                        mv.angular.z= -0.5;
                        mv.linear.x=0.0;
                        pub.publish(mv);
                }






                if (datax4<0.38 || datax5<0.38 || datax6<0.38)                  //izquierda
                {
                        moves="NO";
                        ROS_INFO_STREAM("GO SONAR");

                        mv.angular.z= 0.5; mv.linear.x=0.0;
                        pub.publish(mv);

                }






                if(datax1>=0.38 && datax2>=0.38 && datax3>=0.38 && datax4>=0.38 && datax5>=0.38 && datax6>=0.38)
                {




                        moves="YES";

                        ROS_INFO_STREAM("PAUSE");



                }
        }
}

int main(int argc, char ** argv) {
        // init ROS
        ros::init(argc, argv, "andreita");
        ros::NodeHandle nh;


        // create a publisher object
        pub = nh.advertise<geometry_msgs::Twist>("/cmd_vel", 1000);
        ///dragon = nh.advertise<std_msgs::String>("/goal", 1000);
        //estrellita = nh.advertise<std_msgs::String>("/wander", 1000);


        //crear subscriber


        ros::Subscriber muevete = nh.subscribe("/semueve", 1000, observo);
        ros::Subscriber obs = nh.subscribe("/esquiva", 1000, observo);
        //r|os::Subscriber acc = nh.subscribe("/accion", 1000, ads);
        ros::Subscriber andy = nh.subscribe("/RosAria/sonar", 1000, hola);
        //  ros::Subscriber ver = nh.subscribe("/cambio", 1000, next);


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
