//all drive pid functions 

#include "vex.h"
#include "robot-config.h"
#include "definitions/init.h"
#include "definitions/autonomous.h"
#include <algorithm>

//pid gains for forward and backward: 
float leftdrivekP = 0.57;
float rightdrivekP = 0.54;
float leftdrivekD = 0.08;
float rightdrivekD = 0.1;
float drivemultiply = 1;

//pid gains for turning: 
float gyroturnkP = 0.0665;
float gyroturnkI = 0.00;
float gyroturnkD = -0.012;
float turnmultiply = 9;

//pid functions: 

double currdriveerror, prevdriveerror, currturnerror, prevturnerror;
double lpidpower, rpidpower;
double leftpower, rightpower;
double maxaccel, accel;
int loopnumber;
double maxpower;
//function for forward pid 
void autoTask::fwdrevpid()
{
  lpidpower = motorpower(currdriveerror, prevdriveerror, leftdrivekP, 0, leftdrivekD);
  rpidpower = motorpower(currdriveerror, prevdriveerror, rightdrivekP, 0, rightdrivekD);
  //calculates left and right drive pid power
  maxaccel = accel * loopnumber;
  //maxaccel increased by accel each 10 ms
  if(currdriveerror > 0) //take the minimum to control speed if it is positive
  {
    leftpower = drivemultiply * std::min({lpidpower, maxpower, maxaccel}); 
    rightpower = drivemultiply * std::min({rpidpower, maxpower, maxaccel});
  }
  else //take the maximum since speed is negative here 
  {
    leftpower = drivemultiply * std::max({lpidpower, -maxpower, -maxaccel});
    rightpower = drivemultiply * std::max({rpidpower, -maxpower, -maxaccel});
  }
  fl.spin(fwd, leftpower, volt);
  ml.spin(fwd, leftpower, volt);
  bl.spin(fwd, leftpower, volt);
  fr.spin(fwd, rightpower, volt);
  mr.spin(fwd, rightpower, volt);
  br.spin(fwd, rightpower, volt);
  //set the drive motor output in volts
  prevdriveerror = currdriveerror;
  currdriveerror = goal - currywheel; //error in inches
  loopnumber++; //increases loopnumber by 1 at the end of each pid loop
}

int turndir;
void autoTask::turnpid()
{
  lpidpower = motorpower(currturnerror, prevturnerror, gyroturnkP, gyroturnkI, gyroturnkD);
  rpidpower = motorpower(currturnerror, prevturnerror, gyroturnkP, gyroturnkI, gyroturnkD);
  //calculates left and right drive pid power
  maxaccel = accel * loopnumber;
  //maxaccel increased by accel each 10 ms
  if(currturnerror > 0)
  {
    leftpower = turnmultiply * std::min({lpidpower, maxpower, maxaccel}); 
    rightpower = turnmultiply * std::min({rpidpower, maxpower, maxaccel});
    //take the minimum to control speed if the error is positive
  }
  else 
  {
    leftpower = turnmultiply * std::max({lpidpower, -maxpower, -maxaccel});
    rightpower = turnmultiply * std::max({rpidpower, -maxpower, -maxaccel});
    //take maximum for turning left, error is negative 
  }
  fl.spin(fwd, leftpower, pct);
  ml.spin(fwd, leftpower, pct);
  bl.spin(fwd, leftpower, pct);
  fr.spin(reverse, rightpower, pct);
  mr.spin(reverse, rightpower, pct);
  br.spin(reverse, rightpower, pct);
  //set the drive motor output in volts
  //left and right in opposite directions
  prevturnerror = currdriveerror;
  currturnerror = goal - currheaddeg; //error in inches
  loopnumber++; //increases loopnumber by 1 at the end of each pid loop
}