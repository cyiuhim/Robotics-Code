#include "main.h"
#include "../include/definitions/auton.hpp"
#include "../include/definitions/devices.hpp"
#include "math.h"
#include "../include/pros/adi.h"
using namespace pros;
int directionconst;
float leftwheelpower, rightwheelpower, leftactualwheelpower, rightactualwheelpower;
double trackerror[drivedelay];
double track = 0;
double tracks = 0;
double setpointdeg;
double goal, previousheading, currentheading;
double headingerror[turndelay];
double maxaccel;
int loopexit, loopnumber;
void Auton::drive(double setpoint, double maxpower, int direction, double maxerror, double timelimit)
{
  //setpoint is always a positive number
  setpointdeg = setpoint / (2.75 * M_PI / 360);
  drivereset();
  trackreset();
  starttime = pros::millis();
  timecount = 0;
  switch(direction)
  /*
  1 = forward
  2 = backward
  */
  {
    case 1:
    directionconst = 1;
    break;
    case 2:
    directionconst = -1;
    break;
    default:
    directionconst = 0;
    break;
  }
  for(int i = 0; i < drivedelay; i++)
  {
    trackerror[i] = (-1) * setpointdeg;
  }
  loopexit = 0;
  loopnumber = 1;
  while(timecount < 1000 * timelimit)
  {
    leftwheelpower = fabs(motorpower((-1) * trackerror[0], (-1) * trackerror[1], drivekP, leftdrivekD));
    rightwheelpower = fabs(motorpower((-1) * trackerror[0], (-1) * trackerror[1], drivekP, rightdrivekD));
    maxaccel = driveaccel * loopnumber;
    leftactualwheelpower = Auton::min(leftwheelpower, maxaccel, maxpower);
    rightactualwheelpower = Auton::min(rightwheelpower, maxaccel, maxpower);

    fl = directionconst * leftactualwheelpower;
    bl = directionconst * leftactualwheelpower;
    fr = directionconst * rightactualwheelpower;
    br = directionconst * rightactualwheelpower;

    track = tr.get_value();
    for(int i = drivedelay - 1; i > 0; i--)
    {
      trackerror[i] = trackerror[i - 1];
    }
    trackerror[0] = track - directionconst * setpointdeg;
    delay(drivedelaytime);
    screenclear();
    loopexit = 1;
    for(int i = 0; i < drivedelay; i++)
    {
      if(fabs(trackerror[i]) > maxerror)
      {
        loopexit = 0;
      }
    }
    if(loopexit == 1)
    {
      break;
    }
    currenttime = pros::millis();
    timecount = currenttime - starttime;
    loopnumber++;
  }
  drivestop();
  screenclear();
  drivereset();
}

void Auton::driveindexing(double driveinches, int intakevelocity, double maxpower, double maxerror, int intake, int uptake, double timelimit)
{
  setpointdeg = driveinches / (2.75 * M_PI / 360);
  drivereset();
  trackreset();
  starttime = pros::millis();
  timecount = 0;
  directionconst = 1;
  for(int i = 0; i < drivedelay; i++)
  {
    trackerror[i] = (-1) * setpointdeg;
  }
  loopexit = 0;
  loopnumber = 1;
  while(timecount < 1000 * timelimit)
  {
    leftwheelpower = motorpower((-1) * trackerror[0], (-1) * trackerror[1], drivekP, leftdrivekD);
    rightwheelpower = motorpower((-1) * trackerror[0], (-1) * trackerror[1], drivekP, rightdrivekD);
    maxaccel = driveaccel * loopnumber;
    leftactualwheelpower = Auton::min(leftwheelpower, maxaccel, maxpower);
    rightactualwheelpower = Auton::min(rightwheelpower, maxaccel, maxpower);
    fl = directionconst * leftactualwheelpower;
    bl = directionconst * leftactualwheelpower;
    fr = directionconst * rightactualwheelpower;
    br = directionconst * rightactualwheelpower;
    if(intake == 1)
    {
      li = intakevelocity;
      ri = intakevelocity;
    }
    if(uptake == 1)
    {
      bu = 120;
      tu = -30;
    }
    tracks = tr.get_value();
    track = directionconst * tracks;
    for(int i = drivedelay - 1; i > 0; i--)
    {
      trackerror[i] = trackerror[i - 1];
    }
    trackerror[0] = track - setpointdeg;
    delay(drivedelaytime);
    screenclear();
    loopexit = 1;
    for(int i = 0; i < drivedelay; i++)
    {
      if(fabs(trackerror[i]) > maxerror)
      {
        loopexit = 0;
      }
    }
    if(loopexit == 1)
    {
      break;
    }
    currenttime = pros::millis();
    timecount = currenttime - starttime;
    loopnumber++;
  }
  drivestop();
  intakestop();
  uptakestop();
  screenclear();
}
/*
void Auton::turn(double setpoint, double maxpower, int direction, double maxerror, double timelimit)
{
  //setpoint is always a positive number
  drivereset();
  starttime = pros::millis();
  timecount = 0;
  switch(direction)

  1 = right/clockwise
  2 = left/counter-clockwise

  {
  case 1:
  directionconst = 1;
  break;
  case 2:
  directionconst = -1;
  break;
  default:
  directionconst = 0;
  break;
  }
  currentlefterror = (-1) * setpoint;
  currentrighterror = (-1) * setpoint;
  previouslefterror = (-1) * setpoint;
  previousrighterror = (-1) * setpoint;
  maxlefterror = currentlefterror;
  maxrighterror = currentrighterror;
  while((abs(currentlefterror) > maxerror || abs(currentrighterror) > maxerror) && timecount < 1000 * timelimit)
  {
    leftwheelpower = abs(motorpower((-1) * currentlefterror, (-1) * previouslefterror, turnkP, leftturnkD));
    rightwheelpower = abs(motorpower((-1) * currentrighterror, (-1) * previousrighterror, turnkP, rightturnkD));
    if(leftwheelpower > maxpower)
    {
      leftactualwheelpower = maxpower;
    }
    else
    {
      leftactualwheelpower = leftwheelpower;
    }
    if(rightwheelpower > maxpower)
    {
      rightactualwheelpower = maxpower;
    }
    else
    {
      rightactualwheelpower = rightwheelpower;
    }
    fl = directionconst * leftactualwheelpower;
    bl = directionconst * leftactualwheelpower;
    fr = directionconst * (-1) * rightactualwheelpower;
    br = directionconst * (-1) * rightactualwheelpower;
    leftavg = abs((fl.get_position() + bl.get_position()) / 2);
    rightavg = abs((fr.get_position() + br.get_position()) / 2);
    previouslefterror = currentlefterror;
    previousrighterror = currentrighterror;
    currentlefterror = leftavg - setpoint;
    currentrighterror = rightavg - setpoint;
    if(currentlefterror > previouslefterror)
    {
      maxlefterror = currentlefterror;
    }
    if(currentrighterror > previousrighterror)
    {
      maxrighterror = currentrighterror;
    }
    delay(20);
    screenclear();
    currenttime = pros::millis();
    timecount = currenttime - starttime;
  }
  drivestop();
  screenclear();
  drivestop();
}
*/
void Auton::gyroturn(double setpoint, double maxpower, int direction, double maxerror, double timelimit)
{
  //setpoint is always a positive number
  previousheading = in.get_rotation();
  currentheading = in.get_rotation();
  loopnumber = 0;
  starttime = pros::millis();
  timecount = 0;
  switch(direction)
  /*
  1 = right/clockwise
  2 = left/counter-clockwise
  */
  {
  case 1:
  directionconst = 1;
  break;
  case 2:
  directionconst = -1;
  break;
  default:
  directionconst = 0;
  break;
  }
  for(int i = 0; i < turndelay; i++)
  {
    headingerror[i] = setpoint;
  }
  loopexit = 0;
  while(timecount < 1000 * timelimit)
  {
    leftwheelpower = motorpower(headingerror[0], headingerror[1], gyroturnkP, gyroturnkD);
    rightwheelpower = motorpower(headingerror[0], headingerror[1], gyroturnkP, gyroturnkD);
    maxaccel = driveaccel * loopnumber;
    leftactualwheelpower = Auton::min(leftwheelpower, maxaccel, maxpower);
    rightactualwheelpower = Auton::min(rightwheelpower, maxaccel, maxpower);
    fl = directionconst * leftactualwheelpower;
    bl = directionconst * leftactualwheelpower;
    fr = directionconst * (-1) * rightactualwheelpower;
    br = directionconst * (-1) * rightactualwheelpower;
    currentheading = in.get_rotation();
    for(int i = turndelay - 1; i > 0; i--)
    {
      headingerror[i] = headingerror[(i - 1)];
    }
    headingerror[0] = (setpoint - fabs(currentheading - previousheading));
    delay(turndelaytime);
    screenclear();
    loopexit = 1;
    for(int i = 0; i < turndelay; i++)
    {
      if(fabs(headingerror[i]) > maxerror)
      {
        loopexit = 0;
      }
    }
    if(loopexit == 1)
    {
      break;
    }
    loopnumber++;
    currenttime = pros::millis();
    timecount = currenttime - starttime;
  }
  pros::lcd::print(2, "track: %f", tracks);

  drivestop();
  screenclear();
  drivestop();
}

void Auton::gyroturnto(double setpoint, double maxpower, int direction, double maxerror, double timelimit)
{
  currentheading = in.get_rotation();
  goal = fabs(setpoint - currentheading);
  gyroturn(goal, maxpower, direction, maxerror, timelimit);
}
