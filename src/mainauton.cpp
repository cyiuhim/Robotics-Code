#include "main.h"
#include "../include/definitions/auton.hpp"
#include "../include/definitions/devices.hpp"
#include "../include/definitions/init.hpp"

using namespace pros;
/*
drive(double setpoint, double maxpower, int direction, double maxerror, double time); (1=forward, 2=backward)
driveindexing(int driveinches, int intakevelocity, double maxpower, double maxerror, double time);
turn(double setpoint, double maxpower, int direction,, double maxerror, double timelimit); (1=right, 2=left)
gyroturn(double setpoint, double maxpower, int direction,, double maxerror, double timelimit); (1=right, 2=left)
****only between -360 degrees and 360 degrees;
uptake(double uptakedegrees, double uptakevelocity, double timelimit);
downtake(double downtakedegrees, double downtakevelocity, double timelimit);
*** downtake only at the flip out
Auton::alignwall(float time, double drivevelocity); **time is in ms

*/
float drivekP = 0.08;
float turnkP = 0.7;
float leftdrivekD = 0.15;
float rightdrivekD = 0.15;
float leftturnkD = 0.06;
float rightturnkD = 0.72;
float gyroturnkP = 0.91;
float gyroturnkD = 0.74;

Auton auton;

void mainauto(int automode, int calibrates)
{
  if(calibrates == 1)
  {
    calibrate();
    delay(2500);
  }
  switch(automode) // 1=test, 2=106 point, 3= match red, 4 = match blue, 5 = new 118
  {
    case 1:
    auton.drive(50, 150, 2, 0.2, 2.4);
    break;
    case 2:
    //auton.drive(15, 70, 1, 0.8, 1.2);
    auton.gyroturn(30, 70, 2, 0.2, 0.8);
    auton.drive(5, 150, 1, 0.8, 0.5);

    auton.downtake(200, 100, 1);
    auton.uptake(400, 100, 1.5);
    //first goal
    auton.drive(4, 150, 2, 0.8, 1);
    auton.gyroturnto(86, 75, 1, 0.2, 1);
    //auton.motormove(-20, -20, 0, 0, 0, 1, 1, 1, 1);

    auton.driveindexing(58, 200, 150, 0.8, 1, 0, 2);
    auton.gyroturnto(-3, 60, 2, 0.2, 1);
    auton.driveindexing(13, 150, 150, 0.8, 0, 1, 0.7);
    auton.uptake(300, 100, 1.5);
    //second goal

    auton.drive(7.5, 150, 2, 0.8, 0.7);
    auton.gyroturnto(103.5, 60, 1, 0.2, 1);
    auton.driveindexing(45, 150, 150, 0.8, 1, 1, 2);
    auton.gyroturnto(30, 60, 2, 0.2, 1);
    auton.drive(28, 150, 1, 0.8, 1.5);
    auton.uptake(300, 90, 1.5);
    //third goal

    auton.drive(7, 150, 2, 0.8, 1);
    auton.gyroturnto(207.5, 75, 1, 0.2, 1.2);
    auton.driveindexing(59, 150, 150, 0.8, 1, 1, 2.3);
    auton.gyroturnto(87, 70, 2, 0.2, 1);
    auton.drive(34, 150, 1, 0.8, 1.2);
    auton.uptake(300, 100, 1.5);
    //fourth goal

    auton.drive(10, 150, 2, 0.8, 1);
    auton.gyroturnto(180, 60, 1, 0.2, 1);
    auton.driveindexing(43, 150, 150, 0.8, 1, 1, 2);
    auton.gyroturnto(135, 70, 2, 0.2, 0.5);
    auton.drive(22.5, 150, 1, 0.8, 1.3);
    auton.uptake(300, 90, 1.5);
    //fifth goal
    auton.drive(11.5, 150, 2, 0.8, 1);
    auton.gyroturnto(270, 70, 1, 0.2, 1);
    auton.driveindexing(51, 150, 150, 0.8, 1, 1, 2.2);
    auton.gyroturnto(177, 70, 2, 0.2, 1);
    auton.drive(12, 150, 1, 0.8, 1);
    auton.uptake(300, 100, 1.5);
    //sixth goal
    auton.drive(9, 70, 2, 0.8, 1);
    auton.gyroturnto(-6, 70, 2, 0.2, 1.5);
    auton.driveindexing(29, 120, 150, 0.8, 1, 1, 1.5);
    auton.gyroturnto(-15, 70, 2, 0.2, 0.5);

    auton.driveindexing(24, -200, 150, 0.8, 1, 0, 1.5);
    auton.drive(7, 100, 2, 0.8, 0.5);
    auton.driveindexing(7, -200, 150, 0.8, 1, 0, 1);
    auton.drive(8, 100, 2, 0.8, 0.5);

    auton.gyroturnto(20, 60, 1, 0.2, 1);
    auton.drive(5, 150, 1, 0.8, 0.5);

    auton.uptake(400, 100, 1.5);
    //center goal
    auton.drive(27, 150, 2, 0.8, 1.7);
    auton.gyroturnto(-90, 70, 2, 0.2, 1);
    auton.driveindexing(41, 150, 150, 0.8, 1, 1, 1.7);
    auton.gyroturnto(-154, 60, 2, 0.2, 1);
    auton.drive(28, 150, 1, 0.8, 1.3);
    auton.uptake(300, 90, 1.5);
    //eighth goal
    auton.drive(27, 150, 2, 0.8, 1.5);
    auton.gyroturnto(32, 70, 1, 0.2, 1.2);
    auton.driveindexing(39, 150, 150, 0.8, 1, 1, 1.6);
    auton.gyroturnto(-90, 70, 2, 0.2, 1);
    auton.drive(40, 150, 1, 0.8, 1);
    auton.uptake(600, 100, 1.5);
    //last goal
    break;



    case 3:

    auton.downtake(250, 100, 1.5);
    delay(200);
    auton.driveindexing(8, 150, 150, 0.8, 1, 1, 0.5);
    auton.uptake(220, 100, 1.5);
    auton.downtake(150, 100, 1.5);

    delay(300);
    //first goal
    auton.drive(65.5, 150, 2, 0.8, 2.2);
    auton.gyroturnto(-65, 70, 2, 0.2, 1);
    auton.drive(30, 150, 1, 0.8, 1.2);
    auton.uptake(500, 100, 1.5);
    auton.gyroturnto(-65, 70, 2, 0.2, 1);

    //second goal
    auton.drive(46, 150, 2, 0.8, 1.6);
    //centre goal
    auton.drive(7, 150, 1, 0.8, 0.5);
    auton.gyroturnto(-118.5, 70, 2, 0.2, 1);
    auton.driveindexing(74, 150, 150, 0.8, 1, 1, 2.3);
    auton.uptake(600, 100, 1.5);
    auton.driveindexing(7, -150, 0, 0.8, 1, 0, 0.7);

    break;
/*
auton.downtake(250, 100, 1.5);
delay(200);
auton.driveindexing(7, 150, 150, 0.8, 1, 1, 0.5);
auton.uptake(220, 100, 1.5);
auton.downtake(150, 100, 1.5);

delay(300);
//first goal
auton.drive(62, 150, 2, 0.8, 2.2);
auton.gyroturnto(-67, 70, 2, 0.2, 1);
auton.drive(30, 150, 1, 0.8, 1.2);
auton.uptake(500, 100, 1.5);
auton.gyroturnto(-67, 70, 2, 0.2, 0.5);

//second goal
auton.drive(46, 150, 2, 0.8, 1.6);
//centre goal
auton.drive(7, 150, 1, 0.8, 0.5);
auton.gyroturnto(-120, 70, 2, 0.2, 1);
auton.driveindexing(72, 60, 150, 0.8, 1, 1, 2);
auton.uptake(600, 100, 1.5);
break;
*/


    case 4:
    auton.downtake(250, 100, 1.5);
    delay(200);
    auton.driveindexing(7, 150, 150, 0.8, 1, 1, 0.5);
    auton.uptake(250, 100, 1.5);
    auton.downtake(150, 100, 1.5);

    delay(300);
    //first goal
    auton.drive(62, 150, 2, 0.8, 2.5);
    auton.gyroturnto(-66, 70, 2, 0.2, 1);
    auton.drive(30, 150, 1, 0.8, 1.2);
    auton.uptake(500, 100, 1.5);
    //second goal
    auton.drive(46, 150, 2, 0.8, 1.6);
    //centre goal
    auton.drive(7, 150, 1, 0.8, 0.5);
    auton.gyroturnto(-118, 70, 2, 0.2, 1);
    auton.driveindexing(74, 150, 150, 0.8, 1, 1, 2);
    auton.uptake(600, 100, 1.5);
    break;

    case 5:
    //first goal
    auton.uptake1(100, 200, 0.3);
    auton.drive(10, 150, 1, 0.8, 0.8);

    auton.gyroturnto(-25, 100, 2, 0.2, 0.5);

    auton.driveindexing(40, 150, 200, 0.8, 1, 1, 1.5);
    auton.gyroturnto(-82, 100, 2, 0.2, 1);
    auton.drive(18, 200, 1, 0.8, 1.4);
    auton.uptake(200, 200, 1);
    //second goal
    auton.drive(40, 150, 2, 0.8, 1.8);
    auton.gyroturnto(50, 100, 1, 0.2, 1);
    auton.driveindexing(40, 150, 200, 0.8, 1, 1, 1.5);
    auton.gyroturnto(-25, 100, 2, 0.2, 1);
    auton.driveindexing(35, 150, 200, 0.8, 1, 1, 1.5);
    auton.uptake(200, 200, 1);
  }



}
