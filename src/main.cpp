/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\cyiuh                                            */
/*    Created:      Mon Apr 03 2023                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// ---- END VEXCODE CONFIGURED DEVICES ----

//REMEMBER TO CHANGE AUTON MODE AND TEST SWITCH BEFORE UPLOADING CODE 

#include "vex.h"
#include "robot-config.h"
#include "definitions/opcontrol.h"
#include "definitions/autonomous.h"
#include "definitions/init.h"

using namespace vex;
competition competition1;
driveTask drivetasks;
autoTask autontask;
odometry odom;

int automode;
//initialize any threads and set any initial values 

double autostart, autoend; //timestamp when auton starts and ends 
void init()  
{
  currx = 0;
  curry = 0;
  setbrake(coast); //set drive train to coast for auton and driver
  drivereset(); //reset drive motors 
  cata.setStopping(brake);
  roller.setStopping(brake);
  trackreset(); //reset tracking wheel encoders 
  rollerspeed = 12; //set max speed of roller as default
  boost.set(false);
  expand1.set(false);
  expand2.set(false); //set the expansions to be holding down the triggers
  in1.calibrate();
  while(in1.isCalibrating()) //let inertial finish calibrating before continuing
  {
    wait(10, msec); 
  }
  thread pscreen(printscreen); //prints screen of terminal
  thread odom_(odom.globalpos); //thread for odometry initialized
}

int testswitch = 1; 
//switches between normal mode (driver) and testing mode (only auton) 
//1 = normal, 2 = test
void auton()
{
  drivereset(); //reset motors
  maxpower = 12; //set to max drive speed first 
  rollerspeed = 127;
  automode = 3; //set auton mode here
  //REMEMBER TO CHANGE THIS BEFORE UPLOADING
  /*
  1 = testing 
  2 = awp
  3 = left
  4 = right
  5 = skills 
  */
  thread drive_(autontask.driving);
  thread roll_(autontask.rolling);
  thread cata_(autontask.cataing);
  autontask.mainauto();
}

void opcontrol1()
{
  setbrake(coast); //set the brake type to coas-t for driver control period
  //calls thread functions and initialize threads
  thread drivethread(drivetasks.drivet);
  thread rollthread(drivetasks.rollt);
  thread catathread(drivetasks.catat);
  thread expandthread(drivetasks.expandt);
}

int main() {
  vexcodeInit();

  if(testswitch == 1) 
  {
    competition1.autonomous(auton);
    competition1.drivercontrol(opcontrol1);
    init();
    while(true) 
    {
      wait(10, msec);
    }
  }
  else //testing autons without comp switch, using controller
  {
    init();
    //runs the auton threads only 
    thread driveauton(autontask.driving);
    thread cataauton(autontask.cataing);
    thread rollauton(autontask.rolling);
    while(true) //breaks this loop if any buttons in the following if conditions are pressed
    {
      this_thread::sleep_for(1);
      if(Controller1.ButtonA.pressing())
      {
        automode = 1;
        break;  
      }
      else if(Controller1.ButtonDown.pressing())
      {
        automode = 2;
        break;
      }
      else if(Controller1.ButtonLeft.pressing())
      {
        automode = 3;
        break;
      }
      else if(Controller1.ButtonRight.pressing())
      {
        automode = 4;
        break;
      }
      else if(Controller1.ButtonUp.pressing())
      {
        automode = 5;
        break;
      }
      else if(Controller1.ButtonB.pressing())
      {
        automode = 6;
        break;

      }
    }
    autostart = Brain.Timer.time(sec); //starts auton timer once the auton button is pressed
    autontask.mainauto();
    
  }
  
  
}
