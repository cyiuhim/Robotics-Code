//drive train functions during the driver control period 

#include "vex.h"
#include "robot-config.h"
#include "definitions/opcontrol.h"
#include "definitions/init.h"

double leftx, lefty;

double fwdpow, turnpow; //the calculated power used for forward/backward and turn movements
double leftpow, rightpow; //the power calculated for left and right motor output

//function for setting drive motor velocities 
void driveTask::drivemotor(double forward, double turn)
{
  fwdpow = forward * fabs(forward) / 100; //quadratic velocity curve
  turnpow = pow(turn, 3) / 10000; 
  leftpow = fwdpow + turnpow;
  rightpow = fwdpow - turnpow;
  fl.spin(fwd, leftpow, pct);
  ml.spin(fwd, leftpow, pct);
  bl.spin(fwd, leftpow, pct);
  fr.spin(fwd, rightpow, pct);
  mr.spin(fwd, rightpow, pct);
  br.spin(fwd, rightpow, pct);
  //set the drive motors to spin, separating left and right velocities 
}

//drive thread
void driveTask::drivet()
{
  while(true)
  {
    leftx = Controller1.Axis4.value();
    lefty = Controller1.Axis3.value();
    //set values for the stick variables 
    drivemotor(lefty, leftx); 
    //call the function to use stick values for drive motor output
    wait(10, msec); //10 millisecond delay to prevent overheating 
  }
}