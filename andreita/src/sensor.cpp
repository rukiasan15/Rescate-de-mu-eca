/*
 * Copyright (C) 2008, Morgan Quigley and Willow Garage, Inc.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *   * Redistributions of source code must retain the above copyright notice,
 *     this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *   * Neither the names of Stanford University or Willow Garage, Inc. nor the names of its
 *     contributors may be used to endorse or promote products derived from
 *     this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

// %Tag(FULLTEXT)%
#include "ros/ros.h"
#include "std_msgs/String.h"
#include <sensor_msgs/PointCloud.h>
#include "ArExport.h"
#include <geometry_msgs/Twist.h>
#include <stdio.h>

using namespace std;

#define RANGE              (1024 / 2)
#define num_sensors        8


ros::Publisher dragon;
ros::Publisher uriel;



void hola(const sensor_msgs::PointCloud::ConstPtr& msg)
{


        geometry_msgs::Twist mv;


        std_msgs::String ik;
        std::stringstream li;

        float datax1=msg->points[0].x;
        float datax2=msg->points[2].x;
        float datax3=msg->points[3].x;
        float datax4=msg->points[4].x;
        float datax5=msg->points[5].x;
        float datax6=msg->points[0].x;


        ROS_INFO_STREAM(datax6);


/*

        if(datax1<0.37 || datax2<0.37 || datax3<0.37)         //derecha
        {


                li <<"NO";
                ik.data = li.str();
                uriel.publish(ik);
                ROS_INFO_STREAM("GO");

                mv.angular.z= -0.5;
                mv.linear.x=0.0;

        }

        if (datax4<0.37 || datax5<0.37 || datax6<0.37) //izquierda
        {

                li <<"NO";
                ik.data = li.str();
                uriel.publish(ik);
                ROS_INFO_STREAM("GO");

                mv.angular.z= 0.5; mv.linear.x=0.0;


        }

        dragon.publish(mv);

        if(datax1>=0.37 && datax2>=0.37 && datax3>=0.37 && datax4>=0.37 && datax5>=0.37 && datax6>=0.37)
        {

                li <<"YES";
                ik.data = li.str();
                uriel.publish(ik);
                ROS_INFO_STREAM("PAUSE");


        }

 */

}


int main(int argc, char **argv)
{

        ros::init(argc, argv, "sonar");

        ros::NodeHandle n;


        ros::Subscriber andy = n.subscribe("/distance_sensors_state/floor_sensor", 1000, hola);

        dragon = n.advertise<geometry_msgs::Twist>("/cmd_vel", 1000);


        uriel = n.advertise<std_msgs::String>("/accion", 1000);


        std_msgs::String ik;
        std::stringstream li;

        li <<"NO";
        ik.data = li.str();
        uriel.publish(ik);

/*        float datax2;


        for(datax2=0.0; datax2<0.40; datax2=datax2+0.01)
        {
                if(datax2<0.37)         //derecha
                {


                        li <<"NO";
                        ik.data = li.str();
                        uriel.publish(ik);
                        ROS_INFO_STREAM("GO");
                }

                if(datax2>=0.37)
                {

                        li <<"YES";
                        ik.data = li.str();
                        uriel.publish(ik);
                        ROS_INFO_STREAM("PAUSE");
                }

                sleep(1000);
        }
 */
        ros::spin();


        return 0;
}
