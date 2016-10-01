//Includes all the headers necessary to use the most common public pieces of the ROS system.
#include <ros/ros.h>
//Use image_transport for publishing and subscribing to images in ROS
#include <image_transport/image_transport.h>
//Use cv_bridge to convert between ROS and OpenCV Image formats
#include <cv_bridge/cv_bridge.h>
//Include some useful constants for image encoding. Refer to: http://www.ros.org/doc/api/sensor_msgs/html/namespacesensor__msgs_1_1image__encodings.html for more info.
#include <sensor_msgs/image_encodings.h>
//Include headers for OpenCV Image processing
#include <opencv2/imgproc/imgproc.hpp>
//Include headers for OpenCV GUI handling
#include <opencv2/highgui/highgui.hpp>

#include "std_msgs/String.h"
#include <sstream>

//Store all constants for image encodings in the enc namespace to be used later.
namespace enc = sensor_msgs::image_encodings;

using namespace cv;
using namespace std;



//Declare a string with the name of the window that we will create using OpenCV where processed images will be displayed.
static const char WINDOW[] = "Image Processed";

//Use method of ImageTransport to create image publisher
image_transport::Publisher pub;

ros::Publisher mov;
ros::Publisher ca;
int h=0, t=0;
string formas[5];

//string colores="OVER";
//string otro="search";
int iLowH = 0;
int iHighH = 10;

int iLowS = 100;
int iHighS = 255;

int iLowV = 100;
int iHighV = 255;







//This function is called everytime a new image is published
void imageCallback(const sensor_msgs::ImageConstPtr& original_image)
{

//Convert from the ROS image message to a CvImage suitable for working with OpenCV for processing
        cv_bridge::CvImagePtr cv_ptr;
        try
        {
                //Always copy, returning a mutable CvImage
                //OpenCV expects color images to use BGR channel order.
                cv_ptr = cv_bridge::toCvCopy(original_image, enc::BGR8);
        }
        catch (cv_bridge::Exception& e)
        {
                //if there is an error during conversion, display it
                ROS_ERROR("tutorialROSOpenCV::Color.cpp::cv_bridge exception: %s", e.what());
                return;
        }

        //  Mat imgHSV;

        //cv::cvtColor(cv_ptr->image, imgHSV, cv::COLOR_BGR2HSV);         //Convert the captured frame from BGR to HSV


        cv::imshow(WINDOW, cv_ptr->image);
//Add some delay in miliseconds. The function only works if there is at least one HighGUI window created and the window is active. If there are several HighGUI windows, any of them can be active.
        cv::waitKey(3);
/**
 * The publish() function is how you send messages. The parameter
 * is the message object. The type of this object must agree with the type
 * given as a template parameter to the advertise<>() call, as was done
 * in the constructor in main().
 */
//Convert the CvImage to a ROS image message and publish it on the "camera/image_processed" topic.
        pub.publish(cv_ptr->toImageMsg());




}

/**
 * This tutorial demonstrates simple image conversion between ROS image message and OpenCV formats and image processing
 */




int main(int argc, char **argv)
{

        ros::init(argc, argv, "image_processor");
        /**
         * NodeHandle is the main access point to communications with the ROS system.
         * The first NodeHandle constructed will fully initialize this node, and the last
         * NodeHandle destructed will close down the node.
         */
        ros::NodeHandle nh;



        //Create an ImageTransport instance, initializing it with our NodeHandle.
        image_transport::ImageTransport it(nh);
        //image_transport::Subscriber sub = it.subscribe("camera/image_raw", 1, imageCallback);
        image_transport::Subscriber sub = it.subscribe("/usb_cam/image_raw", 1, imageCallback);


        //OpenCV HighGUI call to destroy a display window on shut-down.
        /**
         * The advertise() function is how you tell ROS that you want to
         * publish on a given topic name. This invokes a call to the ROS
         * master node, which keeps a registry of who is publishing and who
         * is subscribing. After this advertise() call is made, the master
         * node will notify anyone who is trying to subscribe to this topic name,
           /    * and they will in turn negotiate a peer-to-peer connection with this
         * node.  advertise() returns a Publisher object which allows you to
         * publish messages on that topic through a call to publish().  Once
         * all copies of the returned Publisher object are destroyed, the topic
         * will be automatically unadvertised.
         *
         * The second parameter to advertise() is the size of the message queue
         * used for publishing messages.  If messages are published more quickly
         * than we can send them, the number here specifies how many messages to
         * buffer up before throwing some away.
         */
        pub = it.advertise("camera/image_processed", 1);






        /**
         * In this application all user callbacks will be called from within the ros::spin() call.
         * ros::spin() will not return until the node has been shutdown, either through a call
         * to ros::shutdown() or a Ctrl-C.
         */
        ros::spin();
        //ROS_INFO is the replacement for printf/cout.
        ROS_INFO("tutorialROSOpenCV::Color.cpp::No error.");

}
