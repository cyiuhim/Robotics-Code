//functions of catapult during autonomous

#include "vex.h"
#include "robot-config.h"
#include "definitions/autonomous.h"
#include "definitions/init.h"

int catamode;
bool catapiston;
vex::competition Competition1;

//catapult thread during autonomous
void autoTask::cataing()
{
  while(true)
  {
    if(competition1.isAutonomous() || testswitch == 2)
    {
      switch(catamode) //switch loop on which mode the cata thread is running
      {
        case 1: //stop the cata
        cata.stop();
        break;
        case 2: //shoot according to how many pistons are activated
        shoot(catapiston);
        catamode = 1;
        break;
        case 3: //reset the cata at the start of the match 
        setcata();
        catamode = 1;
        break;
      }
    }
    wait(10, msec);
    
  }
}

//function for shooting using (piston1 = 0/1/2) pistons
void autoTask::shoot(bool piston1)
{
  while(catalimit.angle(deg) > catabottomlimit) //let the cata spin to bottom
  {
    cata.spin(fwd, 120, rpm);
    wait(5, msec);
  }
  if(piston1)
  {
    boost.set(true);
  }
  shootcata();
  boost.set(false);
  setcata(); //reload the cata
}

