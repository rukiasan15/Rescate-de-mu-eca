/**
 * Simple shape detector program.
 * It loads an image and tries to find simple shapes (rectangle, triangle, circle, etc) in it.
 * This program is a modified version of `squares.cpp` found in the OpenCV sample dir.
 */
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <cmath>
#include <iostream>
#include <ros/ros.h>
//Use image_transport for publishing and subscribing to images in ROS
#include <image_transport/image_transport.h>
//Use cv_bridge to convert between ROS and OpenCV Image formats
#include <cv_bridge/cv_bridge.h>
//Include some useful constants for image encoding. Refer to: http://www.ros.org/doc/api/sensor_msgs/html/namespacesensor__msgs_1_1image__encodings.html for more info.
#include <sensor_msgs/image_encodings.h>

namespace enc = sensor_msgs::image_encodings;

using namespace cv;
using namespace std;



//Declare a string with the name of the window that we will create using OpenCV where processed images will be displayed.
static const char WINDOW[] = "Image Processed";

//Use method of ImageTransport to create image publisher
image_transport::Publisher pub;



void imageCallback(const sensor_msgs::ImageConstPtr& original_image)
{

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



								cv::Mat imgHSV;


								cv::cvtColor(cv_ptr->image, imgHSV, cv::COLOR_BGR2HSV); //Convert the captured frame from BGR to HSV

								cv::Mat imgThresholded;

								cv::inRange(imgHSV, Scalar(49, 50, 50), Scalar(80, 255, 255), imgThresholded);

								cv::erode(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );
								cv::dilate( imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );

								cv::dilate( imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );
								cv::erode(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );

								Moments oMoments = moments(imgThresholded);

								double dArea = oMoments.m00;


								std::vector<std::vector<cv::Point> > contours;
								std::vector<cv::Point> approx;


								if(dArea>10000)
								{

																cv::Mat contourOutput = imgThresholded.clone();
																cv::findContours( contourOutput, contours, CV_RETR_LIST, CV_CHAIN_APPROX_NONE );




																//	ROS_INFO_STREAM(contours.size());
																//Draw the contours
																cv::Mat contourImage(cv_ptr->image.size(), CV_8UC3, cv::Scalar(0,0,0));
																cv::Scalar colors[3];
																colors[0] = cv::Scalar(255, 0, 0);
																colors[1] = cv::Scalar(0, 255, 0);
																colors[2] = cv::Scalar(0, 0, 255);

																for (int idx = 0; idx < contours.size(); idx++)
																{
																								//	approxPolyDP(idx, approx, arcLength(idx), true) * 0.01, true);
																								cv::approxPolyDP(cv::Mat(contours[idx]), approx, cv::arcLength(cv::Mat(contours[idx]), true)*0.02, true);

																								if(approx.size()==4)
																								{

																																cv::drawContours(contourImage, contours, idx, colors[idx % 3]);
																								}
																}


																cv::imshow("Contours", contourImage);
																//	cvMoveWindow("Contours", 200, 0);
								}
								cv::imshow("DETECT", imgThresholded); //show the thresholded image



//Display the image using OpenCV
								cv::imshow(WINDOW, cv_ptr->image);
//Add some delay in miliseconds. The function only works if there is at least one HighGUI window created and the window is active. If there are several HighGUI windows, any of them can be active.
								cv::waitKey(3);
								pub.publish(cv_ptr->toImageMsg());



}

int main(int argc, char **argv)
{

								ros::init(argc, argv, "image_processor");
								/**
								 * NodeHandle is the main access point to communications with the ROS system.
								 * The first NodeHandle constructed will fully initialize this node, and the last
								 * NodeHandle destructed will close down the node.
								 */
								ros::NodeHandle nh;


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

								return 0;
}
