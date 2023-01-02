// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// LeftIntake           motor         2               
// RightIntake          motor         9               
// FrontLeft            motor         4               
// FrontRight           motor         3               
// Lift                 motor         8               
// IntakeArm            motor         6               
// BackRight            motor         12              
// BackLeft             motor         20              
// IntakeSensor         line          A               
// ---- END VEXCODE CONFIGURED DEVICES ----
#include "vex.h"
#include "robot-config.h"

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*        Description: Competition template for VCS VEX V5                   */
/*                                                                           */
/*---------------------------------------------------------------------------*/
int dummyvariable;
int stateofbuttonR2;
//Creates a competition object that allows access to Competition methods.
vex::rotationUnits deg= vex::rotationUnits::deg;
vex::competition    Competition;
//
//vex::velocityUnits pct = vex::velocityUnits::pct;
/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the cortex has been powered on and    */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/



void pre_auton( void ) {
  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
    //LeftIntake.setVelocity(90,vex::velocityUnits::pct);
    //RightIntake.setVelocity(90,pct);
    //DriveLeft.setVelocity(60,pct);
    //DriveRight.setVelocity(60, pct);
    //Lift.setVelocity(50,pct);
    //set stopping mode for motors
    LeftIntake.setStopping(brake);
    RightIntake.setStopping(brake);
    FrontLeft.setStopping(brake);
    FrontRight.setStopping(brake);
    BackLeft.setStopping(brake);
    BackRight.setStopping(brake);
    Lift.setStopping(hold);
    IntakeArm.setStopping(hold);
    }     


/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/
void setliftvelocity(int velocitys)
{
  Lift.setVelocity(velocitys,vex::velocityUnits::pct);
}
void setintakevelocity(int intakevelocity)
{
  LeftIntake.setVelocity(intakevelocity,vex::velocityUnits::pct);
  RightIntake.setVelocity(intakevelocity,vex::velocityUnits::pct);
}
void setdrivevelocity(int drivevelocity)
{
  BackLeft.setVelocity(drivevelocity,vex::velocityUnits::pct);
  BackRight.setVelocity(drivevelocity,vex::velocityUnits::pct);
  FrontLeft.setVelocity(drivevelocity,vex::velocityUnits::pct);
  FrontRight.setVelocity(drivevelocity,vex::velocityUnits::pct);
}

void drive(int drivedegrees, int drivemode)
{
  switch(drivemode)
  /*drivemode:
  1:go forward
  2:go backward
  3:turn left
  4:turn right
  */
  {
  case 1:
  /*BackLeft.startRotateFor(drivedegrees-50,vex::rotationUnits::deg);
  BackRight.startRotateFor((-1)*drivedegrees+50,vex::rotationUnits::deg);
  FrontLeft.startRotateFor(drivedegrees-50,vex::rotationUnits::deg);
  FrontRight.rotateFor((-1)*drivedegrees+50,vex::rotationUnits::deg);
  setdrivevelocity(10);
  BackLeft.startRotateFor(50,vex::rotationUnits::deg);
  BackRight.startRotateFor((-1)*50,vex::rotationUnits::deg);
  FrontLeft.startRotateFor(50,vex::rotationUnits::deg);
  FrontRight.rotateFor((-1)*50,vex::rotationUnits::deg);
  setdrivevelocity(currentdrivevelocity);*/
  BackLeft.startRotateFor(drivedegrees,vex::rotationUnits::deg);
  BackRight.startRotateFor((-1)*drivedegrees,vex::rotationUnits::deg);
  FrontLeft.startRotateFor(drivedegrees,vex::rotationUnits::deg);
  FrontRight.rotateFor((-1)*drivedegrees,vex::rotationUnits::deg);

  break;
  case 2:
  /*setdrivevelocity(currentdrivevelocity);
  BackLeft.startRotateFor((-1)*drivedegrees+50,vex::rotationUnits::deg);
  BackRight.startRotateFor(drivedegrees-50,vex::rotationUnits::deg);
  FrontLeft.startRotateFor((-1)*drivedegrees+50,vex::rotationUnits::deg);
  FrontRight.rotateFor(drivedegrees-50,vex::rotationUnits::deg);
  setdrivevelocity(10);
  BackLeft.startRotateFor((-1)*50,vex::rotationUnits::deg);
  BackRight.startRotateFor(50,vex::rotationUnits::deg);
  FrontLeft.startRotateFor((-1)*50,vex::rotationUnits::deg);
  FrontRight.rotateFor(50,vex::rotationUnits::deg);
  setdrivevelocity(currentdrivevelocity);*/
   BackLeft.startRotateFor((-1)*drivedegrees,vex::rotationUnits::deg);
  BackRight.startRotateFor(drivedegrees,vex::rotationUnits::deg);
  FrontLeft.startRotateFor((-1)*drivedegrees,vex::rotationUnits::deg);
  FrontRight.rotateFor(drivedegrees,vex::rotationUnits::deg);

  break;
  case 3:
  BackLeft.startRotateFor((-1)*drivedegrees,vex::rotationUnits::deg);
  BackRight.startRotateFor((-1)*drivedegrees,vex::rotationUnits::deg);
  FrontLeft.startRotateFor((-1)*drivedegrees,vex::rotationUnits::deg);
  FrontRight.rotateFor((-1)*drivedegrees,vex::rotationUnits::deg);
  break;
  case 4:
  BackLeft.startRotateFor(drivedegrees,vex::rotationUnits::deg);
  BackRight.startRotateFor(drivedegrees,vex::rotationUnits::deg);
  FrontLeft.startRotateFor(drivedegrees,vex::rotationUnits::deg);
  FrontRight.rotateFor(drivedegrees,vex::rotationUnits::deg);
  break;
  default:
  drivedegrees = 0;
  }
  
}
void intake(int intakedegrees)
{
  LeftIntake.startRotateFor((-1)*intakedegrees,vex::rotationUnits::deg);
  RightIntake.rotateFor(intakedegrees,vex::rotationUnits::deg);
}
void driveintake(int drivedegrees, int intakedegrees)
{
  /*BackLeft.startRotateFor(drivedegrees-50,vex::rotationUnits::deg);
  BackRight.startRotateFor((-1)*drivedegrees+50,vex::rotationUnits::deg);
  FrontLeft.startRotateFor(drivedegrees-50,vex::rotationUnits::deg);
  FrontRight.startRotateFor((-1)*drivedegrees+50,vex::rotationUnits::deg);
  LeftIntake.startRotateFor(intakedegrees-200,vex::rotationUnits::deg);
  RightIntake.rotateFor((-1)*intakedegrees+200,vex::rotationUnits::deg);
  setdrivevelocity(10);
  BackLeft.startRotateFor(50,vex::rotationUnits::deg);
  BackRight.startRotateFor((-1)*50,vex::rotationUnits::deg);
  FrontLeft.startRotateFor(50,vex::rotationUnits::deg);
  FrontRight.startRotateFor((-1)*50,vex::rotationUnits::deg);
  LeftIntake.startRotateFor(200,vex::rotationUnits::deg);
  RightIntake.rotateFor((-1)*200,vex::rotationUnits::deg);
  setdrivevelocity(currentdrivevelocity);
  */
  BackLeft.startRotateFor(drivedegrees,vex::rotationUnits::deg);
  BackRight.startRotateFor((-1)*drivedegrees,vex::rotationUnits::deg);
  FrontLeft.startRotateFor(drivedegrees,vex::rotationUnits::deg);
  FrontRight.startRotateFor((-1)*drivedegrees,vex::rotationUnits::deg);
  LeftIntake.startRotateFor(intakedegrees,vex::rotationUnits::deg);
  RightIntake.rotateFor((-1)*intakedegrees,vex::rotationUnits::deg);
}
void liftstack()
{
  setliftvelocity(80);
  Lift.rotateTo(550,vex::rotationUnits::deg);
  setliftvelocity(40);
  Lift.rotateTo(840,vex::rotationUnits::deg);
}
void setliftstopping(brakeType stop1)
{
  Lift.setStopping(stop1);
}
void setdrivestopping(brakeType stopping)
{
  BackLeft.setStopping(stopping);
  BackRight.setStopping(stopping);
  FrontLeft.setStopping(stopping);
  FrontRight.setStopping(stopping);
}
void intakearm(int intakearmdegrees1, int intakearmdegrees2)
{
  IntakeArm.rotateTo(intakearmdegrees1,vex::rotationUnits::deg);
  intake(-300);
  IntakeArm.rotateTo(intakearmdegrees2,vex::rotationUnits::deg);
}
void setintakearmvelocity(int intakearmvelocity)
{
  IntakeArm.setVelocity(intakearmvelocity,vex::velocityUnits::pct);
}
void setintakearmstopping(brakeType tostop)
{
  IntakeArm.setStopping(tostop);
}
void drivespin(double time)
{
  Brain.Timer.reset();
  while(Brain.Timer.value() < time)
  {
  FrontLeft.spin(vex::directionType::fwd);
  FrontRight.spin(vex::directionType::rev);
  BackLeft.spin(vex::directionType::fwd);
  BackRight.spin(vex::directionType::rev);
  }
}
void drivestop()
{
  FrontLeft.stop();
  FrontRight.stop();
  BackLeft.stop();
  BackRight.stop();
}
void lift(int liftdegrees)
{
  Lift.rotateFor(liftdegrees,vex::rotationUnits::deg);
}
void strafe(int strafedegrees)
{
  FrontLeft.startRotateFor(strafedegrees,vex::rotationUnits::deg);
  FrontRight.startRotateFor(strafedegrees,vex::rotationUnits::deg);
  BackLeft.startRotateFor((-1)*strafedegrees,vex::rotationUnits::deg);
  BackRight.rotateFor((-1)*strafedegrees,vex::rotationUnits::deg);

}
void strafedrive(int strafedegrees, int drivedegrees)
{
  FrontLeft.startRotateFor(strafedegrees - drivedegrees,vex::rotationUnits::deg);
  FrontRight.startRotateFor(strafedegrees + drivedegrees,vex::rotationUnits::deg);
  BackLeft.startRotateFor((-1)*strafedegrees - drivedegrees,vex::rotationUnits::deg);
  BackRight.rotateFor((-1)*strafedegrees + drivedegrees,vex::rotationUnits::deg);

}
void intakearm(int intakearm)
{
  IntakeArm.rotateTo(intakearm,vex::rotationUnits::deg);
}
void intakearmdrive(int intakearm, int drivedegrees)
{
    IntakeArm.startRotateTo(intakearm,vex::rotationUnits::deg);
  FrontLeft.startRotateFor(drivedegrees,vex::rotationUnits::deg);
    FrontRight.startRotateFor((-1)*drivedegrees,vex::rotationUnits::deg);
  BackLeft.startRotateFor(drivedegrees,vex::rotationUnits::deg);
  BackRight.rotateFor((-1)*drivedegrees,vex::rotationUnits::deg);

}
void drivelift(int drivedegrees, int liftdegrees)
{
  Lift.startRotateTo(liftdegrees,vex::rotationUnits::deg);
  FrontLeft.startRotateFor(drivedegrees,vex::rotationUnits::deg);
  FrontRight.startRotateFor((-1)*drivedegrees,vex::rotationUnits::deg);
  BackLeft.startRotateFor(drivedegrees,vex::rotationUnits::deg);
  BackRight.rotateFor((-1)*drivedegrees,vex::rotationUnits::deg);

}
void alignwithwallrev(double sec)
{
  Brain.Timer.reset();
  while(Brain.Timer.value() < sec)
  {
    FrontLeft.spin(vex::directionType::rev);
        FrontRight.spin(vex::directionType::fwd);
    BackLeft.spin(vex::directionType::rev);
    BackRight.spin(vex::directionType::fwd);

  }
}
void alignwithwallrstrafe(double sec)
{
  Brain.Timer.reset();
  while(Brain.Timer.value() < sec)
  {
    FrontLeft.spin(vex::directionType::fwd);
        FrontRight.spin(vex::directionType::fwd);
    BackLeft.spin(vex::directionType::rev);
    BackRight.spin(vex::directionType::rev);

  }
}
void alignwithwalllstrafe(double sec)
{
  Brain.Timer.reset();
  while(Brain.Timer.value() < sec)
  {
    FrontLeft.spin(vex::directionType::rev);
        FrontRight.spin(vex::directionType::rev);
    BackLeft.spin(vex::directionType::fwd);
    BackRight.spin(vex::directionType::fwd);

  }
}
void setleftvelocity(int leftvelocity)
{
  FrontLeft.setVelocity(leftvelocity,vex::velocityUnits::pct);
  BackLeft.setVelocity(leftvelocity,vex::velocityUnits::pct);

}
void setrightvelocity(int rightvelocity)
{
  FrontLeft.setVelocity(rightvelocity,vex::velocityUnits::pct);
  BackLeft.setVelocity(rightvelocity,vex::velocityUnits::pct);

}
void intakestop()
{
  LeftIntake.stop();  
  RightIntake.stop();

}
void driveintakespin(double spintime, int drivedirection)
{
  Brain.Timer.reset();
  switch(drivedirection)
  {
    case 1:
    while(Brain.Timer.value() < spintime)
    {
    FrontLeft.spin(vex::directionType::fwd);
    FrontRight.spin(vex::directionType::rev);
    BackLeft.spin(vex::directionType::fwd);
    BackRight.spin(vex::directionType::rev);
    LeftIntake.spin(vex::directionType::rev);
    RightIntake.spin(vex::directionType::fwd);
    }
    break;
    case 2:
    while(Brain.Timer.value() < spintime)
    {
    FrontLeft.spin(vex::directionType::rev);
    FrontRight.spin(vex::directionType::fwd);
    BackLeft.spin(vex::directionType::rev);
    BackRight.spin(vex::directionType::fwd);
    LeftIntake.spin(vex::directionType::rev);
    RightIntake.spin(vex::directionType::fwd);
    }
    break;
    case 3:
    while(Brain.Timer.value() < spintime)
    {
    FrontLeft.spin(vex::directionType::rev);
    FrontRight.spin(vex::directionType::rev);
    BackLeft.spin(vex::directionType::rev);
    BackRight.spin(vex::directionType::rev);
    LeftIntake.spin(vex::directionType::rev);
    RightIntake.spin(vex::directionType::fwd);
    }
    break;
    case 4:
    while(Brain.Timer.value() < spintime)
    {
    FrontLeft.spin(vex::directionType::fwd);
    FrontRight.spin(vex::directionType::fwd);
    BackLeft.spin(vex::directionType::fwd);
    BackRight.spin(vex::directionType::fwd);
    LeftIntake.spin(vex::directionType::rev);
    RightIntake.spin(vex::directionType::fwd);
    }
    break;
  }
  drivestop();
  intakestop();
}
void setleftstop(brakeType left)
{
  FrontLeft.setStopping(left);
  BackLeft.setStopping(left);
}
void setrightstop(brakeType right)
{
  FrontRight.setStopping(right);
  BackRight.setStopping(right);
}
void autonomous() 
{
  /*
  setintakearmvelocity(100);
  setdrivevelocity(50);
  setintakevelocity(100);
   intakearm(500);
   intakearm(300);
   intakearmdrive(0,300);
   setdrivevelocity(35);
   driveintake(500,1300);
   setdrivevelocity(55);
   drive(600,2);
   setdrivevelocity(100);
   strafe(-900);
   drive(100,3);
   setdrivevelocity(35);
   driveintake(1100,2600);
   drive(860,3);
   setdrivevelocity(70);
   setliftvelocity(50);
   intake(-180);
   drivelift(1400,840);
   setintakevelocity(30);
   setdrivevelocity(30);
   driveintake(-300,-300);
   */
  //above is 7 point auto
  //below is 6 point auto
  /*
  setdrivevelocity(35);
  setintakearmvelocity(80);
  setintakevelocity(100);
  intakearm(400);
  intakearm(0);
  intake(-200);
  driveintake(1000,3000);
  strafe(400);
  driveintake(300,800);
  setdrivevelocity(60);
  alignwithwallrev(2);
  //drive(80,1);
  drive(510,3);
  intake(-280);
  setliftvelocity(60);
  drivelift(750,840);
  vex::task::sleep(400);
  intake(-280);
  drive(300,2);
  */
  //below is 5 point auto
  
  setdrivevelocity(55);
  setintakevelocity(127);
  setintakearmvelocity(127);
  intakearm(500);
  intakearm(0);
  driveintake(1400,3700);
  setdrivevelocity(65);
  driveintake(-1250,800);
  vex::task::sleep(500);
  setdrivevelocity(15);
  drive(300,4);
  //alignwithwallrstrafe(1);
  setdrivevelocity(50);
  drivespin(1.7);
  drive(50,2);
  setintakevelocity(40);
  intake(200);
  liftstack();
  intake(200);
  drive(300,2);
  
  /*
  setdrivevelocity(35);
  setintakevelocity(100);
  setintakearmvelocity(80);
  driveintakespin(2,1);
  setleftvelocity(0);

  driveintakespin(3,1);
  setleftvelocity(35);
  driveintakespin(2.5,1);
  */
}

/*----------------------------------------------------------------------------*/
/*                                                                            */
/*                              User Control Task                             */
/*                                                                            */
/*  This task is used to control your robot during the user control phase of  */
/*  a VEX Competition.                                                        */
/*                                                                            */
/*  You must modify the code to add your own robot specific commands here.    */
/*----------------------------------------------------------------------------*/

  
    


void intakearmup()
{ 
  IntakeArm.spin(vex::directionType::fwd,127,vex::velocityUnits::pct);
  
  
}
void intakearmdown()
{
  IntakeArm.spin(vex::directionType::rev,127,vex::velocityUnits::pct);
}
void stoplift()
 {
    Lift.stop();
 } 

void stopintakearm()
{
  IntakeArm.stop();

}
void intakecontrol()
{
  LeftIntake.spin(vex::directionType::fwd,Controller1.Axis2.value(),vex::velocityUnits::pct);
  RightIntake.spin(vex::directionType::rev,Controller1.Axis2.value(),vex::velocityUnits::pct);
}
int strafeconstant;
void strafe()
{
  if(Lift.position(vex::rotationUnits::deg) < 600)
  {
    strafeconstant = 0;
  }
  else
  {
    strafeconstant = 0;
  }
}

void chassisdrive()
{
  BackLeft.spin(vex::directionType::fwd,Controller1.Axis4.value() + Controller1.Axis3.value() - Controller1.Axis1.value() * strafeconstant,vex::velocityUnits::pct);
  BackRight.spin(vex::directionType::fwd,Controller1.Axis4.value() - Controller1.Axis3.value() - Controller1.Axis1.value() * strafeconstant,vex::velocityUnits::pct);
  FrontLeft.spin(vex::directionType::fwd,Controller1.Axis4.value() + Controller1.Axis3.value() + Controller1.Axis1.value() * strafeconstant,vex::velocityUnits::pct);
  FrontRight.spin(vex::directionType::fwd,Controller1.Axis4.value() - Controller1.Axis3.value() + Controller1.Axis1.value() * strafeconstant,vex::velocityUnits::pct);

}
  void liftup()
  { 
  if(Lift.position(vex::rotationUnits::deg) < 550)
  {
    setliftvelocity(90);
    Lift.spin(vex::directionType::fwd);
    vex::task::sleep(10);
  }
  else if(Lift.position(vex::rotationUnits::deg) >= 550 && Lift.position(vex::rotationUnits::deg) < 920)
  {
    setliftvelocity(60);
    Lift.spin(vex::directionType::fwd);
    vex::task::sleep(10);
  }
  else
  {
    Lift.stop();
  }
  }

void liftdown()
{
  if(Lift.position(vex::rotationUnits::deg) > 0)
  {
    setliftvelocity(100);
    Lift.spin(vex::directionType::rev);
    vex::task::sleep(1);
  }
}
void liftcontrol()
{
  if(!Controller1.ButtonL1.pressing() && !Controller1.ButtonL2.pressing())
  {
    stoplift();
  }
  else if(Controller1.ButtonL1.pressing())
  {
    liftup();
  }
  else if(Controller1.ButtonL2.pressing())
  {
    liftdown();
  }
  
  vex::task::sleep(1);
}
void intakearmcontrol()
{
  Controller1.ButtonR1.pressed(intakearmup);
  Controller1.ButtonR1.released(stopintakearm);
  Controller1.ButtonR2.pressed(intakearmdown);
  Controller1.ButtonR2.released(stopintakearm);
        
}
void usercontrol() {
  // User control code here, inside the loop
  /*
  Driver controls:
  L1: intake 25% L2: intake 75%
  R1: out take 50% R2: out take 100%
  Axis2>0: liftup Axis2<0: liftdown
  while pressed Arrowup:intakearmrotatefwd
        released: rotate to zero
  
  */ 
    while(true)
    { 
      chassisdrive();
      liftcontrol();
      intakecontrol();
      intakearmcontrol();
      strafe();
        }
         vex::task::sleep(20);
    
 
    //Sleep the task for a short amount of time to prevent wasted resources. 
}


//
// Main will set up the competition functions and callbacks.
//
int main() {
    
    //Run the pre-autonomous function. 
    pre_auton();
    
    //Set up callbacks for autonomous and driver control periods.
    Competition.autonomous( autonomous );
    Competition.drivercontrol( usercontrol );

    //Prevent main from exiting with an infinite loop.                        
    while(1) {
      vex::task::sleep(100);//Sleep the task for a short amount of time to prevent wasted resources.
    }    
} 
