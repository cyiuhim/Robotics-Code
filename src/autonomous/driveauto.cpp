//functions of driver thread and setting goal distances/headings using odom during autonomous

#include "vex.h"
#include "robot-config.h"
#include "definitions/autonomous.h"
#include "definitions/init.h"



int drivemode; 



//driver thread during autonomous
void autoTask::driving()
{
  maxpower = 12;
  while(true)
  {
    if(competition1.isAutonomous() || testswitch == 2)
    {
      switch(drivemode) 
      {
        case 1: //stop the drive
        drivestop();
        break;
        case 2: //drive forward or backward
        fwdrevpid();
        if(Brain.timer(sec) > stoptime) //runs the movement in background until it reaches stop time
        {
          drivemode = 1;
        }
        break;
        case 3: //turning right or left
        turnpid();
        if(Brain.timer(sec) > stoptime) //runs the movement in background until it reaches stop time
        {
          drivemode = 1;
        }
        break;
        default: 
        wait(10, msec);
        break;
      }
    }
    
    wait(10, msec);
  }
}

double yheading, xheading, reducedbearing, fullbearing, goaldistance, adjustheading, inertialbearing, inertialbackbearing, goalheading;
//function for calculating heading to a certain point
double autoTask::calcheading(double startx, double starty, double endx, double endy) 
//calculate heading value towards a goal point that is closest to the current heading value
{
  goaldistance = sqrt(pow(endx - startx, 2) + pow(endy - starty, 2));
  yheading = endy - starty;
  xheading = endx - startx;
  reducedbearing = fabs(asin(yheading / goaldistance));
  //reduced bearing using trig graph
  if(yheading >= 0 && xheading >= 0)
  {
    fullbearing = reducedbearing * 180 / M_PI;
  }
  else if(yheading >= 0 && xheading < 0)
  {
    fullbearing = 180 - reducedbearing * 180 / M_PI;
  }
  else if(yheading < 0 && xheading < 0)
  {
    fullbearing = 180 + reducedbearing * 180 / M_PI;
  }
  else 
  {
    fullbearing = 360 - reducedbearing * 180 / M_PI;
  }
  //full bearing with the cast/trig graph
  inertialbearing = 90 - fullbearing;
  adjustheading = -floor((inertialbearing - currheaddeg + 180) / 360);
  goalheading = inertialbearing + adjustheading * 360;
  //adjust bearing to become inertial heading
  return goalheading;
}

//calculate heading so that back is facing the goal point now
double autoTask::calcbackheading(double startx, double starty, double endx, double endy)
{
  goaldistance = sqrt(pow(endx - startx, 2) + pow(endy - starty, 2));
  yheading = endy - starty;
  xheading = endx - startx;
  reducedbearing = fabs(asin(yheading / goaldistance));
  if(yheading >= 0 && xheading >= 0)
  {
    fullbearing = reducedbearing * 180 / M_PI;
  }
  else if(yheading >= 0 && xheading < 0)
  {
    fullbearing = 180 - reducedbearing * 180 / M_PI;
  }
  else if(yheading < 0 && xheading < 0)
  {
    fullbearing = 180 + reducedbearing * 180 / M_PI;
  }
  else 
  {
    fullbearing = 360 - reducedbearing * 180 / M_PI;
  }
  inertialbearing = 90 - fullbearing;
  inertialbackbearing = 180 + inertialbearing;
  adjustheading = -floor((inertialbackbearing - currheaddeg + 180) / 360);
  goalheading = inertialbackbearing + adjustheading * 360;
  return goalheading;
}