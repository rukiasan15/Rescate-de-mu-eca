http://www.cyberbotics.com/forums_attachments/694/braitenberg.c

/*
 * File:         braitenberg.c
 * Date:         September 1st, 2006
 * Description:  A controller moving various robots using the Braitenberg method.
 * Author:       Simon Blanchoud
 *
 * Copyright (c) 2008 Cyberbotics - www.cyberbotics.com
 */

#include <string.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>


#define MAX_SENSOR_NUMBER  16
#define RANGE              (1024 / 2)
#define PI                 3.141592653589793
#define TIME_STEP          64
#define THRESHOLD          90
#define num_sensors        8

// map configuration
#define MAP_SIZE           128  // N by N square grid
#define CELL_SIZE          0.0390625 // => X [m] width and height


// this is the angle at which the IR sensors are placed on the robot
//TODO: Get these directly from robot definition
//static float angle_offset[NB_DIST_SENS] = {-2.4571, 2.9098, 2.3179, 1.8023, 1.3377, 0.8221, 0.2302, -0.8871, -1.57};

int display_width;
int display_height;

// Instantiate odometry track and goto structures

// The map structure (just an integer array)
short map[MAP_SIZE][MAP_SIZE];

// the robot position on the maps
int robot_x = MAP_SIZE / 2;
int robot_y = MAP_SIZE / 2;

static double range = 2000;
static int time_step = 32;

//sensor weights
static double matrix[14][2] = 
        { {-5000, -5000}, {-20000, 40000}, {-30000, 50000}, {-70000, 70000}, {70000, -60000},
        {50000, -40000}, {40000, -20000}, {-5000, -5000}, {-10000, -10000}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0} };


// this is the angle at which the IR sensors are placed on the robot
//TODO: Get these directly from robot definition



/*
 * Those 2 functions do the coordinate transform between the world coordinates (w)
 * and the map coordinates (m) in X and Y direction.
 */

/*
 * Set the coresponding cell to 1 (occupied)
 * and display it
 */
void occupied_cell(int x, int y, float theta)
{ 
  // wb_display_set_color(display,0x000000);
  if (x < 0 || y < 0)
  {
    printf("Error %i %i %f \n", x,y,theta);
    return;
  }
  // normalize angle
  while (theta > PI) {
    theta -= 2*PI;
  }
  while (theta < -PI) {
    theta += 2*PI; 
  } 
  
  // front cell
  if (-PI/6 <= theta && theta <= PI/6) {
    if (y+1 < MAP_SIZE) {
      map[x][y+1] = 1;

    }
  }
  // right cell  
  if (PI/3 <= theta && theta <= 2*PI/3) { 
    if (x+1 < MAP_SIZE) {
      map[x+1][y] = 1;


    }
  }

  // left cell
  if (-2*PI/3 <= theta && theta <= -PI/3) {
    if (x-1 > 0) {
      map[x-1][y] = 1;

    }
  } 
  // back cell
  if (5*PI/6 <= theta || theta <= -5*PI/6) {
    if (y-1 > 0) {
      map[x][y-1] = 1;


    }
  } 
}

static void run(void)
{
  int i, j;
  double speed[2];
  double sensors_value[MAX_SENSOR_NUMBER];



    /*
     * The Braitenberg algorithm is really simple, it simply computes the
     * speed of each wheel by summing the value of each sensor multiplied by
     * its corresponding weight. That is why each sensor must have a weight 
     * for each wheel.
     */
    for (i = 0; i < 2; i++) {
        speed[i] = 0.0;

        for (j = 0; j < num_sensors; j++) {

            /* 
             * We need to recenter the value of the sensor to be able to get
             * negative values too. This will allow the wheels to go 
             * backward too.
             */
            speed[i] += matrix[j][i] * (1.0 - (sensors_value[j] / range));
        }
    }



}


int main()
{
  initialize();



  while (1) {
    
        // update the odometric position
    odometry_track_step(&ot);
    
    // update position on the map
    robot_x = wtom(ot.result.x);
    robot_y = wtom(ot.result.y);

    run();
    

    //Draw robot's dot
    wb_display_set_color(display,0x00FF00);
    wb_display_draw_rectangle(display,robot_x, display_height-robot_y-1,1,1);
 
    /* Run simulation */
    wb_robot_step(time_step);

    }
  
  
   // Necessary to cleanup webots stuff
  wb_robot_cleanup();
  return 0;
}



