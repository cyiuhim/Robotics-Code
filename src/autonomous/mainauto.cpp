//all autonomous routines here

#include "vex.h"
#include "robot-config.h"
#include "definitions/autonomous.h"
#include "definitions/init.h"

bool printtime; //records auton time, true when auton is running and false after auton ended

//only for testing, pid, odom, use button A
void autoTask::testing()
{
  turn(180, 1);
}

//solo awp, 6 discs, 2 rollers
void autoTask::awp()
{
  drivemultiply = 2;
  drive(-5, 0.3);
  drivemultiply = 1;
  setbrake(hold);
  rollerdeg(250, 1); //first roller
  setbrake(coast);
  drive(5, 0.4);
  rollermode = 2;
  drivemultiply = 1.3;
  gotopointback(-9.5, 9, 0.8, 1); //picks up third disc
  drivemultiply = 1;
  drive(11, 0.7);
  turntopoint(-18, 100, 0.8); //turns to goal 
  driveshoot(10, 2.5, 0.09, 0.15); //first shot 
  setbrake(hold);
  
  drivestop();
  rollermode = 1;
  wait(0.3, sec);
  setbrake(coast);
  /*
  turntopointback(17, 23, 0.7);
  intake.set(true);
  rollermode = 2;
  
  driveintake(-18, 0.9, 0.3);
  maxpower = 8;
  drive(-9, 0.8);
  maxpower = 12;
  turntopoint(-14, 100, 0.8);
  rollermode = 3;
  driveshoot(10, 3, 0.1, 0.1); //second shot
  setbrake(hold);
  
  drivestop();
  wait(0.2, sec);
  setbrake(coast);
  */
  gotopointback(31, 16, 0.7, 1.2);
  gotopointback(35, 41, 0.7, 1.1);
  //go around the triple stack
  rollermode = 2;
  maxpower = 8.5;
  gotopointback(67, 71, 0.7, 2); //intake row of three discs
  maxpower = 12;
  turntopoint(-6, 110, 0.7); //turns to goal
  drive(-3, 0.4);
  driveshoot(5, 0.56, 0.09, 0.15); //second shot
  setbrake(hold);
  
  drivestop();
  wait(0.2, sec);
  setbrake(coast);
  rollermode = 1;
  gotopointback(92, 105, 0.75, 1.3); 
  rollerdeg(250, 1);
  //second roller
}

//starts on left side, 9 discs, 1 roller
void autoTask::leftauto()
{
  drivemultiply = 2;
  drive(-5, 0.3);
  drivemultiply = 1;
  setbrake(hold);
  rollerdeg(250, 1); //first roller
  setbrake(coast);
  drive(8, 0.4);
  rollermode = 2;
  drivemultiply = 1.3;
  gotopointback(-8, 8, 0.8, 1); //picks up third disc
  drivemultiply = 1;
  drive(12.5, 0.7);
  turntopoint(-17, 100, 0.8); //turns to goal 
  driveshoot(10, 1, 0.07, 0.15); //first shot 
  setbrake(hold);
  
  drivestop();
  rollermode = 1;
  wait(0.3, sec);
  setbrake(coast);
  turntopointback(17.5, 20.5, 0.7); //turns to triple stack
  intake.set(true);
  rollermode = 2;
  
  driveintake(-16, 0.9, 0.6); 
  //drives to the stack intaking, then putting the intake down
  maxpower = 8;
  drive(-8, 0.6);
  maxpower = 12;
  turntopoint(-9.5, 100, 0.8); //turn to goal 
  driveshoot(10, 0.18, 0.04, 0.15); //second shot 
  setbrake(hold);
  
  drivestop();
  wait(0.2, sec);
  setbrake(coast);
  rollermode = 2;
  gotopointback(45.5, 36.5, 0.7, 0.9); //intake first disc next to low goal
  turntopointback(49, 16, 0.7);
  maxpower = 7;
  drivetopointback(49, 16, 1.15); //intake other two discs next to low goal 
  maxpower = 12;
  drive(5, 0.2);
  gotopoint(30, 28, 0.6, 0.9); //goes to shooting position 
  rollermode = 3; 
  turntopoint(-9, 100, 0.6); //turn to goal 
  driveshoot(10, 0.2, 0.04, 0.18); //third shot 
    setbrake(hold);
  
  drivestop();
  wait(0.2, sec);
  setbrake(coast);
}

//starts on right side, 6 discs, 1 roller
void autoTask::rightauto()
{
  drive(-20, 0.9);
  turn(95, 0.7);
  drive(-11, 0.6);
  rollerdeg(250, 1); //first roller
  drive(10, 0.5);
  rollermode = 2;
  turntopointback(22.5, 6, 0.9);
  maxpower = 12;
  drivetopointback(22.5, 6, 1.5); //intakes first disc on the row
  maxpower = 12;
  //rollermode = 1;
  turntopoint(100, -32, 0.8); //turn to goal 
  
  //setbrake(hold);
  driveshoot(5, 0.42, 0.1, 0.2); //first shot
  setbrake(hold);
  
  drivestop();
  wait(0.2, sec);
  setbrake(coast);
  //setbrake(coast);
  rollermode = 2;
  //drivemultiply = 1.3;
  gotopointback(35, 17, 0.7, 1); //intakes second disc on the row
  gotopointback(30, 30.5, 0.6, 1); //intakes first disc next to low goal 
  drivemultiply = 1.7;
  gotopointback(22, 32, 0.6, 1.2); //intakes second disc next to low goal 
  drivemultiply = 1;
  turntopoint(27, 14, 0.8);
  rollermode = 3;
  //rollermode = 1;
  drivetopoint(27, 14, 1); //go to shooting position 
  turntopoint(100, -32, 0.7); //turn to goal
  driveshoot(8, 0.25, 0.07, 0.2); //second shot 
  setbrake(hold);
  drivestop();
}
void autoTask::skills()
{
  drivemultiply = 2;
  drive(-5, 0.3);
  drivemultiply = 1;
  setbrake(hold);
  rollerdeg(-650, 1); //first roller
  setbrake(coast);
  drive(6, 0.4);
  rollermode = 2;
  drivemultiply = .85;
  gotopointback(-25, 20.1, .7, 1.2); //picks up third disc
  drivemultiply = 2;
  rollermode = 1;
  drive(-5.5, 0.3);
  drivemultiply = 1;
  setbrake(hold);
  rollerdeg(-800, 1); //second roller
  setbrake(coast);
  drive(6, 0.6);
  wait(0.2, sec);
  gotopoint(-21, 66.5, 1.2, 1.35); 
  shoot(); // first shot

  wait(350, msec);
  rollermode = 2;
  gotopointback(-3, 48, .8, 1.3);
  gotopointback(22, 71, 1, 1.35); 
  turntopoint(-20, 114.5, 0.65);
  driveshoot(3, 0.6, 0, .9); //second shot

  drive(-6, 0.8);
  intake.open();
  gotopointback(40, 88, .9, 1.3); 
  intake.close();
  drive(-2, 1.1);
  turntopoint(-19, 111, 0.65);
  drive(15.5, 0.8);
  shoot(); // third shot

  wait(300, msec);
  intake.open();
  gotopointback(58, 94.5, .9, 1.5); 
  intake.close();
  wait(700, msec);
  gotopointback(92, 93, .3, 1.5); 
  drivemultiply = 2;
  rollermode = 1;
  drive(-6, 0.4);
  drivemultiply = 1;
  setbrake(hold);
  rollerdeg(-650, 1); //third roller
  setbrake(coast);
  gotopoint(67.2, 99, .3, 1.5); 
  gotopointback(67.2, 119, .9, 1.5); 

  drivemultiply = 2;
  rollermode = 1;
  drive(-6, 0.4);
  drivemultiply = 1;
  setbrake(hold);
  rollerdeg(-650, 1); //fourth roller
  setbrake(coast);
  drive(10, 0.7);
  gotopoint(85, 70, 0.7, 1.5);
  gotopoint(86.1, 52.5, 0.6, 1.5);
  shoot(); //fourth shot 
  wait(0.5, sec);
  rollermode = 2;
  gotopointback(70, 72, 0.7, 1.4);
  gotopointback(45, 51, 0.8, 1.3);
  turntopoint(87, 5, 0.7);
  driveshoot(5, 1.5, 0, 0.8); //fifth shot
  rollermode = 2;
  drive(-5, 0.7);
  intake.set(true);
  gotopointback(25.5, 30.5, 0.7, 1.4);
  intake.set(false);
  wait(1.2, sec);
  turntopoint(87, 5, 0.7);
  drive(17, 1);
  shoot(); //sixth shot 
  wait(0.5, sec);
  intake.set(true);
  gotopointback(5.5, 24.5, 0.5, 1.3);
  intake.set(false);
  drive(-7, 0.6);
  turntopoint(87, 5, 0.6);
  drive(40, 2);
  shoot(); //seventh shot
  wait(0.5, sec);
  gotopointback(-11.5, 15, 1, 2);
  turntopoint(85, 100, 1);
  expansion();
  wait(0.5, sec);
  drive(-13, 1);
}

//main auton function that controls which auton to run
void autoTask::mainauto()
{
  printtime = true; //starts auton
  switch(automode)
  {
    case 1: 
    testing();
    break;
    case 2: 
    awp();
    break;
    case 3: 
    leftauto();
    break;
    case 4: 
    rightauto();
    break;
    case 5:
    skills();
    break;
    default: 
    wait(10, msec);
  }
  printtime = false; //stops timer after finishing the full auton 
}