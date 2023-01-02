#include "main.h"
#include "math.h"
#include "../include/definitions/auton.hpp"
#include "../include/definitions/devices.hpp"

double starttime, timecount, currenttime;

int Auton::motorpower(double currenterror, double previouserror, float kP, float kD)
{
  float pterm = currenterror * kP;
  float dterm = (currenterror - previouserror) * kD;
  float power = pterm + dterm;
  return power;
}

double Auton::min(double value1, double value2, double value3)
{
  if(value1 < value2 && value1 < value3)
  {
    return value1;
  }
  else if(value2 < value3)
  {
    return value2;
  }
  else
  {
    return value3;
  }
}
void Auton::drivestop()
{
  fl = 0;
  fr = 0;
  bl = 0;
  br = 0;
}

void Auton::intakestop()
{
  li = 0;
  ri = 0;
}

void Auton::uptakestop()
{
  tu = 0;
  bu = 0;
}

void Auton::trackreset()
{
  tr.reset();
}

void Auton::drivereset()
{
  fl.tare_position();
  fr.tare_position();
  bl.tare_position();
  br.tare_position();
}

void Auton::uptakereset()
{
  tu.tare_position();
  bu.tare_position();
}

void Auton::screenclear()
{
  for(int i = 0; i <= 7; i++)
  {
    lcd::clear_line(i);
  }
}

void Auton::uptake(double uptakedegrees, double uptakevelocity, double timelimit)
{
  uptakereset();
  starttime = pros::millis();
  timecount = 0;
  while(tu.get_position() < uptakedegrees && timecount < 1000 * timelimit)
  {
    tu = uptakevelocity;
    bu = uptakevelocity;
    pros::delay(2);
    currenttime = pros::millis();
    timecount = currenttime - starttime;
  }
  uptakestop();
}

void Auton::uptake1(double uptakedegrees, double uptakevelocity, double timelimit)
{
  uptakereset();
  starttime = pros::millis();
  timecount = 0;
  while(tu.get_position() < uptakedegrees && timecount < 1000 * timelimit)
  {
    bu = uptakevelocity;
    pros::delay(2);
    currenttime = pros::millis();
    timecount = currenttime - starttime;
  }
  uptakestop();
}

void Auton::downtake(double uptakedegrees, double uptakevelocity, double timelimit)
{
  uptakereset();
  starttime = pros::millis();
  timecount = 0;
  while(tu.get_position() > (-1) * uptakedegrees && timecount < 1000 * timelimit)
  {
    tu = (-1) * uptakevelocity;
    bu = (-1) * uptakevelocity;
    pros::delay(2);
    currenttime = pros::millis();
    timecount = currenttime - starttime;
  }
  uptakestop();
}

void Auton::motormove(double leftvel, double rightvel, double invel, double botvel, double topvel, int dstop, int instop, int upstop, int time)
{
  drivereset();
  uptakereset();
  starttime = pros::millis();
  timecount = 0;
  while(timecount < 1000 * time)
  {
    fl = leftvel;
    bl = leftvel;
    fr = rightvel;
    br = rightvel;
    li = invel;
    ri = invel;
    bu = botvel;
    tu = topvel;
    pros::delay(2);
    currenttime = pros::millis();
    timecount = currenttime - starttime;
  }
  if(dstop == 1)
  {
    drivestop();
  }
  if(instop == 1)
  {
    intakestop();
  }
  if(upstop == 1)
  {
    uptakestop();
  }
}
