#include <iostream>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <ros/ros.h>

using namespace cv;
using namespace std;

int main( int argc, char** argv )
{
        VideoCapture cap(0); //capture the video from web cam

        if ( !cap.isOpened() ) // if not success, exit program
        {
                cout << "Cannot open the web cam" << endl;
                return -1;
        }

//        namedWindow("Control", CV_WINDOW_AUTOSIZE); //create a window called "Control"

        int iLowH = 160;
        int iHighH = 179;

        int iLowS = 100;
        int iHighS = 255;

        int iLowV = 100;
        int iHighV = 255;


        while (true)
        {
                Mat imgOriginal;

                bool bSuccess = cap.read(imgOriginal); // read a new frame from video

                if (!bSuccess) //if not success, break loop
                {
                        cout << "Cannot read a frame from video stream" << endl;
                        break;
                }

                Mat imgHSV;

                cvtColor(imgOriginal, imgHSV, COLOR_BGR2HSV); //Convert the captured frame from BGR to HSV

                Mat imgThresholded;

                inRange(imgHSV, Scalar(iLowH, iLowS, iLowV), Scalar(iHighH, iHighS, iHighV), imgThresholded); //Threshold the image



                //morphological opening (remove small objects from the foreground)
                erode(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );
                dilate( imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );

                //morphological closing (fill small holes in the foreground)
                dilate( imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );
                erode(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );

                Moments oMoments = moments(imgThresholded);

                double dM01 = oMoments.m01;
                double dM10 = oMoments.m10;
                double dArea = oMoments.m00;

                int posX = dM10 / dArea;
                int posY = dM01 / dArea;

                Mat dist;
                magnitude(posX, posY, dist);

                imshow("Thresholded Image", imgThresholded); //show the thresholded image
                imshow("Original", imgOriginal); //show the original image



                if (waitKey(30) == 27) //wait for 'esc' key press for 30ms. If 'esc' key is pressed, break loop
                {
                        cout << "esc key is pressed by user" << endl;
                        break;
                }
        }

        return 0;

}
