//controlling expansion during driver control period 

#include "vex.h"
#include "robot-config.h"
#include "definitions/opcontrol.h"
#include "definitions/init.h"

bool b,y;

//expansion thread during driver control period 
void driveTask::expandt()
{
  
  while(true)
  {
    b = Controller1.ButtonB.pressing();
    y = Controller1.ButtonY.pressing();
    if(b && y) //if buttons b and y pressed TOGETHER then expand
    {
      expansion();
      Controller1.Screen.print(1);
      break; //ends the thread when expanded
    }
    wait(10, msec);
  }
}