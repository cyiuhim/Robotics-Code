//all odometry functions 

#include "vex.h"
#include "robot-config.h"
#include "definitions/init.h"

double currx, curry, prevx, prevy, currhead, prevhead, currheaddeg;
double currxwheel, currywheel, prevxwheel, prevywheel;
double xtrackmove, ytrackmove, headingdiff;
double xchange, ychange;
double deltax, deltay;
double inertialdrift = 357.6; //the amount of degrees inertial sensor registers after one rotation of robot
//measure each time for tuning

double xtrackdis = -3.96; //the prependicular distance between x tracking wheel and the tracking center 
double ytrackdis = -3.00; //the prependicular distance between y tracking wheel and the tracking center 
/*
for tuning: spin the robot clockwise, then use the formula: 
xtrackdis = ((degrees of x tracking wheel) / 360 * 2.75 * pi) / ((inertial heading degrees) / 180 * pi)
          = (xtrack in inches) / (inertial in radians)
same for y track, but replace x with y
*/

extern double initheading;

//function for updating sensor values for x,y tracking wheels and inertial sensor
void odometry::updatesensor() //updates sensor values 
{
  //update previous sensor values
  prevxwheel = currxwheel;
  prevywheel = currywheel;
  prevhead = currhead;
  //update current sensor values
  currxwheel = xtrack.position(deg) * 2.75 * M_PI / 360; //convert degrees to inches, 2.75 inch wheels
  currywheel = ytrack.position(deg) * 2.75 * M_PI / 360; //the y tracking wheel is reversed, hence negative
  currheaddeg = in1.rotation(deg) * 360/inertialdrift; //accounts for inertial drift, current heading in degrees 
  currhead = currheaddeg * M_PI / 180; //change deg to rad
}

//function for calculating x y coordinate change in global heading
void odometry::calcposdiff() //see photos in robotics/photos/odom
{
  //below is using 5225a document
  //calculates movement of tracking wheels and heading
  xtrackmove = currxwheel - prevxwheel;
  ytrackmove = currywheel - prevywheel;
  headingdiff = currhead - prevhead;
  //calculate deltax and deltay, which is the coordinate change with respect the axes set at CURRENT heading of robot
  if(headingdiff != 0) 
  {
    if((ytrackmove > 0 && headingdiff > 0) || (ytrackmove < 0 && headingdiff < 0)) //if arc to the right
    {
      deltax = 2 * sin(headingdiff / 2) * (xtrackmove / headingdiff + xtrackdis);
      deltay = 2 * sin(headingdiff / 2) * (ytrackmove / headingdiff + ytrackdis);
    }
    else //if arc to the left
    {
      deltax = 2 * sin(headingdiff / 2) * (xtrackmove / headingdiff + xtrackdis);
      deltay = 2 * sin(headingdiff / 2) * (ytrackmove / headingdiff + ytrackdis);
    }
  }
  else //use just tracking wheel change if no change in heading, avoid dividing by 0
  {
    deltax = xtrackmove;
    deltay = ytrackmove;
  }
  xchange = cos(prevhead) * deltax + sin(prevhead) * deltay;
  ychange = -sin(prevhead) * deltax + cos(prevhead) * deltay;
  //coordinate changes with respect to GLOBAL heading
}

void odometry::globalpos()
{
  currx = 0;
  curry = 0;
  //only resets once at start of match 
  while(true)
  {
    updatesensor();
    calcposdiff();
    currx += xchange;
    curry += ychange;
    wait(5, msec);
    //5ms intervals for the brain to update
  }
}