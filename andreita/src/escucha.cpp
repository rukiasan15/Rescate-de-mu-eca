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
#include <sstream>
#include <stdlib.h>

using namespace std;
int i=0, j=0, k=0;

ros::Publisher xa;
string pl[50];
string word;
//string choco="nada", canela="nada";


/**
 * This tutorial demonstrates simple receipt of messages over the ROS system.
 */
void chatterCallback(const std_msgs::String::ConstPtr& msg)
{

        std_msgs::String st;
        std::stringstream sp;


        word=msg->data.c_str();

//ROS_INFO("I heard: [%s]", msg->data.c_str());

        if(word=="ROVER1") { i=0; }
        if(word!="ROVER1")


        {

                i++;

                if(i==2)
                {
                        /*    if(word=="AMARILLO") { word="VERDE"; }
                            if(word=="ROJO") { word="ROSADO"; }*/

                        pl[j]=word;
                        j++;
                        sp<<word;

                        st.data = sp.str();
                        xa.publish(st);

                }

        }


        if(word=="OVER")
        {

                sp<<word;

                st.data = sp.str();
                xa.publish(st);

                pl[j]=word;

                ROS_INFO_STREAM("hola");

                /*  sp<<pl[k];

                   st.data = sp.str();
                   xa.publish(st);
                 */
        }





}





int main(int argc, char **argv)
{
        ros::init(argc, argv, "escucha");

        ros::NodeHandle n;

        // ros::Subscriber sub = n.subscribe("/chatter", 1000, chatterCallback);
        ros::Subscriber Hsub = n.subscribe("/hola", 1000, chatterCallback);
        //  ros::Subscriber xander = n.subscribe("/cambio", 1000, chatterCallback);

        xa = n.advertise<std_msgs::String>("/plan", 1000);






        ros::spin();


// %EndTag(SPIN)%

        return 0;
}
// %EndTag(FULLTEXT)%
