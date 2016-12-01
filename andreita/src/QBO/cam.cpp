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

#include "sensor_msgs/PointCloud2.h"

#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>

#include "std_msgs/String.h"
#include <sstream>

//Store all constants for image encodings in the enc namespace to be used later.
namespace enc = sensor_msgs::image_encodings;

using namespace cv;
using namespace std;

void centro (int,int,int,int);

void esquivar_izquierda(int);

void esquivar_derecha(int);

//Declare a string with the name of the window that we will create using OpenCV where processed images will be displayed.
static const char WINDOW[] = "Image Processed";

//Use method of ImageTransport to create image publisher
image_transport::Publisher pub;

ros::Publisher mov;
ros::Publisher ca;
int h=0, t=0;
string colores[5], otro="wait";



//string colores="OVER";
//string otro="search";
int iLowH = 0;
int iHighH = 10;

int iLowS = 100;
int iHighS = 255;

int iLowV = 100;
int iHighV = 255;

int x=NULL, x2=NULL, y=NULL, y2=NULL;


       
//int RposX=NULL, VposX=NULL, NposX=NULL, RposX2=NULL, VposX2=NULL, NposX2=NULL;




//recibe la imagen que llega de la camara derecha

void imageRight(const sensor_msgs::ImageConstPtr& original_image)
{



      //creacion de mensajes
        std_msgs::String gi;
        std::stringstream si;

  //envia mensajes para dejar siempre el canal enviando
                        gi.data = si.str();
                        mov.publish(gi);

//creacion de vectores para reconocer formas
        std::vector<std::vector<cv::Point> > contours;
        std::vector<cv::Point> approx;

        std::vector<std::vector<cv::Point> > contoR;
        std::vector<cv::Point> approxR;

        std::vector<std::vector<cv::Point> > contoN;
        std::vector<cv::Point> approxN;

        std::vector<std::vector<cv::Point> > contoA;
        std::vector<cv::Point> approxA;

        std::vector<std::vector<cv::Point> >contoV;
        std::vector<cv::Point> approxV;







//si es igual a over es que llego al final del plan
        if(colores[t]=="OVER")
        {
                si <<"no veo un color";
                gi.data = si.str();
                mov.publish(gi);
                //colores="FINISH";
        }

//si colores es diferente de OVER es que aun tiene colores por seguir en el plan y otro cuando es GO es que ya todo esta listo
//para empezar
        if(colores[t]!="OVER" && otro=="GO")

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

//matriz de imagen
                cv::Mat imgHSV;





//compara que color tiene en ese momento para mandar el codigo de color
                if(colores[t]=="ROSADO") { iLowH=160; iLowS=100; iLowV=100; iHighH=179; iHighS=255; iHighV=255; }
                if(colores[t]=="AMARILLO") { iLowH=15; iLowS=50; iLowV=50; iHighH=40; iHighS=255; iHighV=255; }
                if(colores[t]=="VERDE") { iLowH=49; iLowS=50; iLowV=50; iHighH=80; iHighS=255; iHighV=255; }
                if(colores[t]=="NARANJA") { iLowH=0; iLowS=100; iLowV=100; iHighH=10; iHighS=255; iHighV=255; }
                if(colores[t]=="AZUL") { iLowH=100; iLowS=65; iLowV=75; iHighH=130; iHighS=255; iHighV=255; }


                cv::cvtColor(cv_ptr->image, imgHSV, cv::COLOR_BGR2HSV); //Convert the captured frame from BGR to HSV y se guarda en imgHSV


//matrices de imagenes, uno por cada color que puede buscar; imgThresholded es el color que buscara en el momento
                cv::Mat imgThresholded, rosado, amarillo, verde, rojo, azul;




                cv::inRange(imgHSV, Scalar(iLowH, iLowS, iLowV), Scalar(iHighH, iHighS, iHighV), imgThresholded); //Threshold the image
                cv::inRange(imgHSV, Scalar(160, 100, 100), Scalar(179, 255, 255), rosado);
                cv::inRange(imgHSV, Scalar(15, 50, 50), Scalar(40, 255, 255), amarillo);
                cv::inRange(imgHSV, Scalar(49, 50, 50), Scalar(80, 255, 255), verde);
                cv::inRange(imgHSV, Scalar(0, 65, 75), Scalar(12, 255, 255), rojo);
                cv::inRange(imgHSV, Scalar(100, 65, 75), Scalar(130, 255, 255), azul);

                //morphological opening (removes small objects from the foreground)
                cv::erode(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );
                cv::dilate( imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );

                cv::erode(rosado, rosado, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );
                cv::dilate( rosado, rosado, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );

                cv::erode(amarillo, amarillo, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );
                cv::dilate( amarillo, amarillo, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );

                cv::erode(verde, verde, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );
                cv::dilate( verde, verde, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );

                cv::erode(rojo, rojo, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );
                cv::dilate( rojo, rojo, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );

                cv::erode(azul, azul, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );
                cv::dilate( azul, azul, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );


                //morphological closing (removes small holes from the foreground)
                cv::dilate( imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );
                cv::erode(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );


                cv::dilate( rosado, rosado, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );
                cv::erode(rosado, rosado, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );

                cv::dilate( amarillo, amarillo, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );
                cv::erode(amarillo, amarillo, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );

                cv::dilate( verde, verde, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );
                cv::erode(verde, verde, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );

                cv::dilate( rojo, rojo, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );
                cv::erode(rojo, rojo, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );

                cv::dilate( azul, azul, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );
                cv::erode(azul, azul, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );





                //Calculate the moments of the thresholded image
                Moments oMoments = moments(imgThresholded);

                double dM01 = oMoments.m01;
                double dM10 = oMoments.m10;
                double dArea = oMoments.m00;

                // srand(time(0));
                // ros::Rate rate(2);


                Moments oRosado = moments(rosado);
                Moments oRojo = moments(rojo);
                Moments oVerde = moments(verde);
                Moments oAzul = moments(azul);


                double rArea = oRosado.m00;
                double vArea = oVerde.m00;
                double nArea = oRojo.m00;


                double rM10 = oRosado.m10;
                double vM10 = oVerde.m10;
                double nM10 = oRojo.m10;


                int RposX = rM10 / rArea;
                int VposX = vM10 / vArea;
                int NposX = nM10 / nArea;


                cv::Mat contourImage(cv_ptr->image.size(), CV_8UC3, cv::Scalar(0,0,0));
                cv::Scalar colors[3];
                colors[0] = cv::Scalar(255, 0, 0);
                colors[1] = cv::Scalar(0, 255, 0);
                colors[2] = cv::Scalar(0, 0, 255);



//si el area del color a buscar es menor a 10000 entonces no estoy viendo el color que estoy buscando
//y tiene que esquivar los demás porque no debe ir alla

                if( dArea<=10000)
                {
                        //  si<<"no veo un color";


                        //ROSADO
                        if(rArea > 10000)
                        {

                                //hace un clon de la imagen de rosado en contROSADO
                                cv::Mat contROSADO = rosado.clone();
                                cv::findContours( contROSADO, contoR, CV_RETR_LIST, CV_CHAIN_APPROX_NONE ); //numero de contornos



                                //recorre todos los lados que ha encontrado
                                for (int r = 0; r < contoR.size(); r++)
                                {
                                        //aproximacion de los contornos
                                        cv::approxPolyDP(cv::Mat(contoR[r]), approxR, cv::arcLength(cv::Mat(contoR[r]), true)*0.02, true);

                                        if(approxR.size()==4 || approxR.size()==5) //si son 4 contornos es un cuadrado
                                        {

                                                //dibuja los contornos
                                                cv::drawContours(contourImage, contoR, r, colors[r % 3]);

                                                ROS_INFO_STREAM("ROSADO");

                                                //esquivar el color
						esquivar_izquierda(RposX);
                                              
                                        }

                                }
                        }






                        //VERDE

                        else if(vArea > 10000)
                        {
                                cv::Mat contVERDE = verde.clone();
                                cv::findContours( contVERDE, contoV, CV_RETR_LIST, CV_CHAIN_APPROX_NONE );




                                for (int v = 0; v < contoV.size(); v++)
                                {
                                        //	approxPolyDP(idx, approx, arcLength(idx), true) * 0.02, true);
                                        cv::approxPolyDP(cv::Mat(contoV[v]), approxV, cv::arcLength(cv::Mat(contoV[v]), true)*0.02, true);
                                        if(approxV.size()==4 || approxV.size()==5)
                                        {
                                                cv::drawContours(contourImage, contoV, v, colors[v % 3]);

                                                ROS_INFO_STREAM("verde");


						esquivar_izquierda(VposX);
                                               
                                        }

                                }
                        }



                        //NARANJA

                       else  if(nArea > 10000)
                        {
                                cv::Mat contNARANJA = rojo.clone();
                                cv::findContours( contNARANJA, contoN, CV_RETR_LIST, CV_CHAIN_APPROX_NONE );




                                for (int n = 0; n < contoN.size(); n++)
                                {
                                        //	approxPolyDP(idx, approx, arcLength(idx), true) * 0.02, true);
                                        cv::approxPolyDP(cv::Mat(contoN[n]), approxN, cv::arcLength(cv::Mat(contoN[n]), true)*0.02, true);
                                        if(approxN.size()==4 || approxN.size()==5)
                                        {
                                                cv::drawContours(contourImage, contoN, n, colors[n % 3]);

                                               
						ROS_INFO_STREAM("NARANJA");
						 esquivar_izquierda(NposX);
                                        }
                                }
                        }






                }

                x = dM10 / dArea;
                y = dM01 / dArea;

// if the area <= 10000, I consider that the there are no object in the image and it's because of the noise, the area is not zero

                if (dArea > 10000)
                {

                       

                        //creacion de mensajes
                        std_msgs::String so;
                        std::stringstream po;

                        //clona imgThresholdeden contourOutput
                        cv::Mat contourOutput = imgThresholded.clone();
                        cv::findContours( contourOutput, contours, CV_RETR_LIST, CV_CHAIN_APPROX_NONE ); //numero de contornos


                        //recorre todos los lados que ha encontrado
                        for (int idx = 0; idx < contours.size(); idx++)
                        {


                                //aproximacion de los lados
                                cv::approxPolyDP(cv::Mat(contours[idx]), approx, cv::arcLength(cv::Mat(contours[idx]), true)*0.02, true);

                                //  ROS_INFO_STREAM(posY);

                                //si son 4 lados o 5 que estan cerca es un cuadrado (el qbo mira los cuadrados raros)
                                if(approx.size()==4 || approx.size()==5)
                                {

 ROS_INFO_STREAM("canelones");
                                     //   ROS_INFO_STREAM(x);


                                        centro(x,x2,y,y2);


                                        //dibuja los lados
                                        cv::drawContours(contourImage, contours, idx, colors[idx % 3]);






                                }
                        }
                }







//aqui termina el dibujado del seguimiento

/*    if(dArea <= 10000 && rArea <= 10000 && vArea <= 10000)
    {

            ROS_INFO_STREAM("NO VEO UN COLOR");

            si <<"no";
            gi.data = si.str();
            mov.publish(gi);


    }
 */
                cv::imshow("Contours", contourImage);

                //muestra en pantalla los lados

                //une en una matriz todas las demas
                imgThresholded = imgThresholded +  rosado +rojo +verde;
                cv::imshow("DETECT", imgThresholded); //show the thresholded image



//Display the image using OpenCV
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



}



/**
 * This tutorial demonstrates simple image conversion between ROS image message and OpenCV formats and image processing
 */


//almacena los colores en un vector
void waypoints(const std_msgs::String::ConstPtr& msg)
{

        ROS_INFO_STREAM("recibo");

        colores[h]= msg->data.c_str();

        ROS_INFO_STREAM(colores[h]<<" "<<colores[t]);
        if(colores[h]=="OVER")
        {
                otro="GO";
        }

        h++;


}



void centro(int x, int x2, int y, int y2)
{
        //creacion de mensajes
        std_msgs::String gi;
        std::stringstream si;

        //creacion de mensajes
        std_msgs::String so;
        std::stringstream po;

ROS_INFO_STREAM(y);
//ROS_INFO_STREAM(y2);
//si esta en el rango que se mueva a la izquierda
        if(x>=132)
        {
                ROS_INFO_STREAM("izquierda");

                si <<"izquierda";
                gi.data = si.str();

        }

        //esta a la derecha y tiene que moverse a alla
        if(x2<=128)
        {
                ROS_INFO_STREAM("derecha");

                si <<"derecha";
                gi.data = si.str();
        }


        //si esta en ese rango esta en el centro
        if(x<=131 && x2>=129)
        {

                if(y>=215 || y2>=215)
                {

                        ROS_INFO_STREAM("llegue al waypoint");
                        po <<"ON";
                        so.data = po.str();
                        ca.publish(so);
    			 t++;

                }

                else
                {
                        ROS_INFO_STREAM("centro");

                        si <<"no";
                        gi.data = si.str();

                }
        }

        mov.publish(gi);



}

void esquivar_izquierda(int C1)
{
      //creacion de mensajes
        std_msgs::String gi;
        std::stringstream si;

	if(C1 >= 132)
	{
 	si <<"evitarI";          ROS_INFO_STREAM("izquierda");
	}
   
   gi.data = si.str();
   mov.publish(gi);


}

void esquivar_derecha(int C2)
{
      //creacion de mensajes
        std_msgs::String gi;
        std::stringstream si;

	if(C2 < 181)
	{
	 si <<"obsDERE";           ROS_INFO_STREAM("derecha");
	}
   
   gi.data = si.str();
   mov.publish(gi);


}




//recibe la imagen que llega de la camara izquierda

void imageLeft(const sensor_msgs::ImageConstPtr& original_image)
{




        //creacion de mensajes

        std_msgs::String gi;
        std::stringstream si;

        //creacion de vectores para reconocer formas
        std::vector<std::vector<cv::Point> > contours;
        std::vector<cv::Point> approx;

        std::vector<std::vector<cv::Point> > contoR;
        std::vector<cv::Point> approxR;

        std::vector<std::vector<cv::Point> > contoN;
        std::vector<cv::Point> approxN;

        std::vector<std::vector<cv::Point> > contoA;
        std::vector<cv::Point> approxA;

        std::vector<std::vector<cv::Point> >contoV;
        std::vector<cv::Point> approxV;





       

        //si es igual a over es que llego al final del plan
        if(colores[t]=="OVER")
        {
                si <<"no veo un color";
                gi.data = si.str();
                mov.publish(gi);
                //colores="FINISH";
        }

        //si colores es diferente de OVER es que aun tiene colores por seguir en el plan y otro cuando es GO es que ya todo esta listo
        //para empezar
        if(colores[t]!="OVER" && otro=="GO")

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

                //matriz de imagen
                cv::Mat imgHSV;





                //compara que color tiene en ese momento para mandar el codigo de color
                if(colores[t]=="ROSADO") { iLowH=160; iLowS=100; iLowV=100; iHighH=179; iHighS=255; iHighV=255; }
                if(colores[t]=="AMARILLO") { iLowH=15; iLowS=50; iLowV=50; iHighH=40; iHighS=255; iHighV=255; }
                if(colores[t]=="VERDE") { iLowH=49; iLowS=50; iLowV=50; iHighH=80; iHighS=255; iHighV=255; }
                if(colores[t]=="NARANJA") { iLowH=0; iLowS=100; iLowV=100; iHighH=10; iHighS=255; iHighV=255; }
                if(colores[t]=="AZUL") { iLowH=100; iLowS=65; iLowV=75; iHighH=130; iHighS=255; iHighV=255; }


                cv::cvtColor(cv_ptr->image, imgHSV, cv::COLOR_BGR2HSV);  //Convert the captured frame from BGR to HSV y se guarda en imgHSV


                //matrices de imagenes, uno por cada color que puede buscar; imgThresholded es el color que buscara en el momento
                cv::Mat imgThresholded, rosado, amarillo, verde, rojo, azul;




                cv::inRange(imgHSV, Scalar(iLowH, iLowS, iLowV), Scalar(iHighH, iHighS, iHighV), imgThresholded);  //Threshold the image
                cv::inRange(imgHSV, Scalar(160, 100, 100), Scalar(179, 255, 255), rosado);
                cv::inRange(imgHSV, Scalar(15, 50, 50), Scalar(40, 255, 255), amarillo);
                cv::inRange(imgHSV, Scalar(49, 50, 50), Scalar(80, 255, 255), verde);
                cv::inRange(imgHSV, Scalar(0, 65, 75), Scalar(12, 255, 255), rojo);
                cv::inRange(imgHSV, Scalar(100, 65, 75), Scalar(130, 255, 255), azul);

                //morphological opening (removes small objects from the foreground)
                cv::erode(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );
                cv::dilate( imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );

                cv::erode(rosado, rosado, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );
                cv::dilate( rosado, rosado, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );

                cv::erode(amarillo, amarillo, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );
                cv::dilate( amarillo, amarillo, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );

                cv::erode(verde, verde, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );
                cv::dilate( verde, verde, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );

                cv::erode(rojo, rojo, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );
                cv::dilate( rojo, rojo, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );

                cv::erode(azul, azul, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );
                cv::dilate( azul, azul, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );


                //morphological closing (removes small holes from the foreground)
                cv::dilate( imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );
                cv::erode(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );


                cv::dilate( rosado, rosado, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );
                cv::erode(rosado, rosado, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );

                cv::dilate( amarillo, amarillo, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );
                cv::erode(amarillo, amarillo, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );

                cv::dilate( verde, verde, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );
                cv::erode(verde, verde, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );

                cv::dilate( rojo, rojo, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );
                cv::erode(rojo, rojo, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );

                cv::dilate( azul, azul, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );
                cv::erode(azul, azul, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );





                //Calculate the moments of the thresholded image
                Moments oMoments = moments(imgThresholded);

                double dM01 = oMoments.m01;
                double dM10 = oMoments.m10;
                double dArea = oMoments.m00;

                // srand(time(0));
                // ros::Rate rate(2);


                Moments oRosado = moments(rosado);
                Moments oRojo = moments(rojo);
                Moments oVerde = moments(verde);
                Moments oAzul = moments(azul);


                double rArea = oRosado.m00;
                double vArea = oVerde.m00;
                double nArea = oRojo.m00;


                double rM10 = oRosado.m10;
                double vM10 = oVerde.m10;
                double nM10 = oRojo.m10;


                int RposX = rM10 / rArea;
                int VposX = vM10 / vArea;
                int NposX = nM10 / nArea;


                cv::Mat contourImage(cv_ptr->image.size(), CV_8UC3, cv::Scalar(0,0,0));
                cv::Scalar colors[3];
                colors[0] = cv::Scalar(255, 0, 0);
                colors[1] = cv::Scalar(0, 255, 0);
                colors[2] = cv::Scalar(0, 0, 255);



                //si el area del color a buscar es menor a 10000 entonces no estoy viendo el color que estoy buscando
                //y tiene que esquivar los demás porque no debe ir alla

                if( dArea<=10000)
                {
                        //  si<<"no veo un color";


                        //ROSADO
                        if(rArea > 10000)
                        {

                                //hace un clon de la imagen de rosado en contROSADO
                                cv::Mat contROSADO = rosado.clone();
                                cv::findContours( contROSADO, contoR, CV_RETR_LIST, CV_CHAIN_APPROX_NONE );  //numero de contornos



                                //recorre todos los lados que ha encontrado
                                for (int r = 0; r < contoR.size(); r++)
                                {
                                        //aproximacion de los contornos
                                        cv::approxPolyDP(cv::Mat(contoR[r]), approxR, cv::arcLength(cv::Mat(contoR[r]), true)*0.02, true);

                                        if(approxR.size()==4 || approxR.size()==5)  //si son 4 contornos es un cuadrado
                                        {

                                                //dibuja los contornos
                                                cv::drawContours(contourImage, contoR, r, colors[r % 3]);

                                                ROS_INFO_STREAM("ROSADO");

                                                //esquivar el color
                                    		esquivar_derecha(RposX);

                                        }

                                }
                        }






                        //VERDE

                        if(vArea > 10000)
                        {
                                cv::Mat contVERDE = verde.clone();
                                cv::findContours( contVERDE, contoV, CV_RETR_LIST, CV_CHAIN_APPROX_NONE );




                                for (int v = 0; v < contoV.size(); v++)
                                {
                                        //	approxPolyDP(idx, approx, arcLength(idx), true) * 0.02, true);
                                        cv::approxPolyDP(cv::Mat(contoV[v]), approxV, cv::arcLength(cv::Mat(contoV[v]), true)*0.02, true);
                                        if(approxV.size()==4 || approxV.size()==5)
                                        {
                                                cv::drawContours(contourImage, contoV, v, colors[v % 3]);

                                                ROS_INFO_STREAM("verde");


                                                esquivar_derecha(VposX);
                                        }

                                }
                        }



                        //NARANJA

                        if(nArea > 10000)
                        {
                                cv::Mat contNARANJA = rojo.clone();
                                cv::findContours( contNARANJA, contoN, CV_RETR_LIST, CV_CHAIN_APPROX_NONE );




                                for (int n = 0; n < contoN.size(); n++)
                                {
                                        //	approxPolyDP(idx, approx, arcLength(idx), true) * 0.02, true);
                                        cv::approxPolyDP(cv::Mat(contoN[n]), approxN, cv::arcLength(cv::Mat(contoN[n]), true)*0.02, true);
                                        if(approxN.size()==4 || approxN.size()==5)
                                        {
                                                cv::drawContours(contourImage, contoN, n, colors[n % 3]);

                                                
					ROS_INFO_STREAM("NARANJA");
					esquivar_derecha(NposX);
                                        
	}
                                }
                        }



                }

                x2 = dM10 / dArea;
                y2 = dM01 / dArea;

                // if the area <= 10000, I consider that the there are no object in the image and it's because of the noise, the area is not zero

                if (dArea > 10000)
                {

                        

                        //creacion de mensajes
                        std_msgs::String so;
                        std::stringstream po;

                        //clona imgThresholdeden contourOutput
                        cv::Mat contourOutput = imgThresholded.clone();
                        cv::findContours( contourOutput, contours, CV_RETR_LIST, CV_CHAIN_APPROX_NONE );  //numero de contornos


                        //recorre todos los lados que ha encontrado
                        for (int idx = 0; idx < contours.size(); idx++)
                        {


                                //aproximacion de los lados
                                cv::approxPolyDP(cv::Mat(contours[idx]), approx, cv::arcLength(cv::Mat(contours[idx]), true)*0.02, true);

                               // ROS_INFO_STREAM("L: "<<x2);

                                //si son 4 lados o 5 que estan cerca es un cuadrado (el qbo mira los cuadrados raros)

                                if(approx.size()==4 || approx.size()==5)
                                {


ROS_INFO_STREAM("canelones");
                                        centro(x,x2,y,y2);





                                        //dibuja los lados
                                        cv::drawContours(contourImage, contours, idx, colors[idx % 3]);






                                }
                        }
                }







                //aqui termina el dibujado del seguimiento

                /*    if(dArea <= 10000 && rArea <= 10000 && vArea <= 10000)
                    {

                            ROS_INFO_STREAM("NO VEO UN COLOR");

                            si <<"no";
                            gi.data = si.str();
                            mov.publish(gi);


                    }
                 */

                //muestra en pantalla los lados
                cv::imshow("Contours 2", contourImage);

                //une en una matriz todas las demas
                imgThresholded = imgThresholded +  rosado +rojo +verde;
                cv::imshow("DETECT 2", imgThresholded);  //show the thresholded image



                //Display the image using OpenCV
                cv::imshow("IZQUIERDA", cv_ptr->image);
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


colores[0]="ROSADO", colores[1]="VERDE", otro="GO";

        mov = nh.advertise<std_msgs::String>("/semueve", 1000);
        ca = nh.advertise<std_msgs::String>("/vueltitas", 1000);

        ros::Subscriber Jo = nh.subscribe("/plan", 1000, waypoints);




        //Create an ImageTransport instance, initializing it with our NodeHandle.
        image_transport::ImageTransport it(nh);

        //image_transport::Subscriber sub = it.subscribe("camera/image_raw", 1, imageCallback);
        //image_transport::Subscriber sub = it.subscribe("/usb_cam/image_raw",1, imageRight);
        image_transport::Subscriber sub = it.subscribe("/stereo/right/image_raw",1, imageRight);
        image_transport::Subscriber sub2 = it.subscribe("/stereo/left/image_raw",1, imageLeft);


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
