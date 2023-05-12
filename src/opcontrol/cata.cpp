//catapult functions during the driver control period 

//tune cata pid constants at init.cpp

#include "vex.h"
#include "robot-config.h"
#include "definitions/opcontrol.h"
#include "definitions/init.h"
#include "definitions/autonomous.h"

bool r1;

bool prevcata, currcata; //variables to detect when the reload button is pressed

//function for controlling cata motor 
void driveTask::catamotor(bool reload)
{ 
  prevcata = currcata;
  currcata = reload;
  if(!prevcata && currcata)//if the catabutton is just pressed
  {
    if(catalimit.angle(deg) < reloaduplimit) //shoot the cata when the cata is down
    {
      shootcata();
      setcata();
    }
    else //just reset cata at the start of program
    {
      setcata();
    }
  }
}

//catapult thread during driver control period 
void driveTask::catat()
{
  while(true)
  {
    r1 = Controller1.ButtonR1.pressing();
    catamotor(r1); //calls catapult control function
    wait(10, msec);
    if(Controller1.ButtonL2.pressing())
    {
      autoTask::shoot(true);
    }
  }
}