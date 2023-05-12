//functions that programming autonomous routines would use, in mainauton.cpp

#include "vex.h"
#include "robot-config.h"
#include "definitions/autonomous.h"
#include "definitions/init.h"

//function for shooting without piston boost
void autoTask::shoot()
{
  catapiston = false;
  catamode = 2;
}

//function for shooting with both piston boosts
void autoTask::shootpiston()
{
  catapiston = true;
  catamode = 2;
}

double starttime, stoptime;
double goal;
double sumerror;
//turn to a certain heading, in a certain limit of time
void autoTask::turn(double goalheading1, double time)
{
  goal = goalheading1; //set goal
  if(goalheading1 > in1.rotation(deg))
  {
    turndir = 1;
  }
  else 
  {
    turndir = -1;
  }
  sumerror = 0;
  loopnumber = 0; //reset acceleration 
  accel = 3;
  starttime = Brain.timer(sec);
  stoptime = starttime + time;
  drivemode = 3;
  wait(time + 0.01, sec); //wait for the drivemode to go back to 1, before going to next line 
}

//drive to a certain distance according to the y tracking wheel in inches, in a time limit
void autoTask::drive(double drivedis, double time)
{
  goal = drivedis + currywheel; 
  loopnumber = 0; //reset acceleration 
  accel = 1;
  starttime = Brain.timer(sec);
  stoptime = starttime + time;
  drivemode = 2;
  wait(time + 0.01, sec); //wait for the drivemode to go back to 1, before going to next line 
}

//drive while shooting 
void autoTask::driveshoot(double drivedis, double accel1, double time1, double time2)
{
  goal = drivedis + currywheel; 
  loopnumber = 0; //reset acceleration 
  accel = accel1;
  starttime = Brain.timer(sec);
  stoptime = starttime + time1 + time2;
  drivemultiply = 3; //gain momentum 
  drivemode = 2;
  wait(time1, sec);
  shootpiston(); //does not stop robot here
  wait(time2, sec);
  drivemultiply = 1; 
}

//drop intake while driving 
void autoTask::driveintake(double drivedis, double time1, double time2)
{
  goal = drivedis + currywheel; 
  loopnumber = 0; //reset acceleration 
  accel = 1;
  starttime = Brain.timer(sec);
  stoptime = starttime + time1 + time2;
  drivemode = 2;
  wait(time1, sec);
  intake.set(false); //does not stop robot here
  wait(time2, sec);

}
//turn to front facing a certain point
void autoTask::turntopoint(double goalx, double goaly, double time)
{
  goal = calcheading(currx, curry, goalx, goaly);
  turn(goal, time);
}

//turn to back facing a certain point
void autoTask::turntopointback(double goalx, double goaly, double time)
{
  goal = calcbackheading(currx, curry, goalx, goaly);
  turn(goal, time);
}

//drive forward for distance between current point and goal
void autoTask::drivetopoint(double goalx, double goaly, double time)
{
  goal = sqrt(pow((goalx - currx), 2) + pow((goaly - curry), 2));
  drive(goal, time);
}

//drive backward for distance between current point and goal 
void autoTask::drivetopointback(double goalx, double goaly, double time)
{
  goal = -sqrt(pow((goalx - currx), 2) + pow((goaly - curry), 2));
  drive(goal, time);
}

//turn then drive forward to goal point
void autoTask::gotopoint(double goalx, double goaly, double turntime, double drivetime)
{
  turntopoint(goalx, goaly, turntime);
  drivetopoint(goalx, goaly, drivetime);
}

//turn then go backwards to goal point
void autoTask::gotopointback(double goalx, double goaly, double turntime, double drivetime)
{
  turntopointback(goalx, goaly, turntime);
  drivetopointback(goalx, goaly, drivetime);
}

double currentroller, startroller, endroller;
//spins the roller by a number of degrees 
void autoTask::rollerdeg(double rollergoal, double rollertime)
{
  currentroller = roller.position(deg);
  startroller = Brain.Timer.time(sec);
  endroller = startroller + rollertime;
  if(rollergoal > 0)
  {
    rollermode = 2;
    while(roller.position(deg) < currentroller + rollergoal && Brain.Timer.time(sec) < endroller)
    {
    wait(10, msec);
    }
  }
  else 
  {
    rollermode = 3;
    while(roller.position(deg) > currentroller + rollergoal && Brain.Timer.time(sec) < endroller)
    {
      wait(10, msec);
    }
  }
  rollermode = 1;
}

