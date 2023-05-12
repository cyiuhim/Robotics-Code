//roller/intake functions during the driver control period 

#include "vex.h"
#include "robot-config.h"
#include "definitions/opcontrol.h"
#include "definitions/init.h"

double righty;
bool r2, previntake, currintake;
int intakeno;
//function for controlling roller motor 
void driveTask::rollermotor(double roller1)
{
  //if the catapult is not down it cannot intake discs
  if(roller1 > 5 && catalimit.angle() < reloaduplimit) //prevent stick drift > 5
  {
    roller.spin(fwd, 12, volt); //spin at max speed whenever stick is pushed up
  }
  else if(roller1 < -5)
  {
    roller.spin(fwd, roller1, pct); //variable speed when stick is pushed down
  }
  else 
  {
    roller.stop(); //prevent motor from spinning when stick is close to center
  }
}

void driveTask::intakelift(bool intake1)
{
  previntake = currintake;
  currintake = intake1;
  //detects if button for intake lift pressed
  if(!previntake && currintake)
  {
    intakeno += 1;
  }
  if(intakeno % 2 == 0)
  {
    intake.set(false);
  }
  else 
  {
    intake.set(true);
  }
}

//roller/intake motor thread 
void driveTask::rollt()
{
  while(true)
  {
    righty = Controller1.Axis2.value();
    r2 = Controller1.ButtonR2.pressing();
    rollermotor(righty); //calls function for roller motor 
    wait(10, msec);
    intakelift(r2);
  }
}