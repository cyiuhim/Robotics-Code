//functions of roller/intake during autonomous

#include "vex.h"
#include "robot-config.h"
#include "definitions/autonomous.h"
#include "definitions/init.h"

double rollerspeed;
int rollermode;

//roller thread during autonomous
void autoTask::rolling()
{
  while(true)
  {
    if(competition1.isAutonomous() || testswitch == 2)
    {
      switch(rollermode)
      {
        case 1: //stop the motor, mostly before turning the rollers to ensure accurate timing
        roller.stop();
        break;
        case 2: //for intaking discs
        if(catalimit.angle() < reloaduplimit)
        {
          roller.spin(fwd, rollerspeed, volt);
        }
        else 
        {
          roller.stop();
        }
        break;
        case 3: //for spinning rollers
        roller.spin(reverse, rollerspeed, volt);
        break;
        default: 
        wait(10, msec);
        break;
      }
    }
    
    wait(10, msec);
  }
}