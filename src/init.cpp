//file for all initializing functions, and functions used for both driver control and autonomous

#include "vex.h"
#include "robot-config.h"
#include "definitions/init.h"
#include "definitions/autonomous.h"
#include "definitions/opcontrol.h"
#include <initializer_list>
#include <algorithm>

double drivetemp, catatemp, rolltemp;
double reloaduplimit = 40.3; //upper limit of the catapult rotation sensor when it is reloading
double reloaddownlimit = 39.8; //lower limit of the catapult rotation sensor when it is reloading 
double catabottomlimit = 36; //bottom limit of the cata, when to start piston boost
double shootlimit = 94; //lower limit of the catapult rotation sensor when the cata is shot 
//also used when to start the cata pid 
double shootrotation = 100; //number of degrees for the catapult motor to spin to shoot 

double currcatadeg; //current cata rotation sensor value 
double catapidspeed; //calculated speed for the catapult during its pid 
double initheading;

double autotime; //number of seconds that auton has already run 

//function for resetting cata at the reload position 
void setcata()
{
  while(catalimit.angle(deg) > reloaddownlimit)
  {
    cata.spin(fwd, 120, rpm);
    
    wait(10, msec); //updates errors every 10 milliseconds 
  }
  cata.stop();
} 

//function for shooting the cata
void shootcata()
{
  currcatadeg = cata.position(deg);
  while(cata.position(deg) < currcatadeg + shootrotation)
  {
    cata.spin(fwd, 120, rpm);
    wait(10, msec);
  }
}

//sets the drive motor brake type
void setbrake(vex::brakeType braking)
{
  fl.setBrake(braking);
  fr.setBrake(braking);
  ml.setBrake(braking);
  mr.setBrake(braking);
  bl.setBrake(braking);
  br.setBrake(braking);
}

//expansion
void expansion()
{
  expand1.set(true);
  expand2.set(true);
}

//print screen function
void printscreen()
{
  while(true)
  {
    if(testswitch == 2) //only if it is in testing mode for temperature check 
    {
      Controller1.Screen.clearScreen();
      
      //limit temperature before overheating: 50 degrees Celsius
      drivetemp = std::max({fl.temperature(celsius), fr.temperature(celsius), ml.temperature(celsius), mr.temperature(celsius), bl.temperature(celsius), br.temperature(celsius)});
      //takes the maximum temperature of the drive motors 
      rolltemp = roller.temperature(celsius);
      catatemp = cata.temperature(celsius);
      //if the temperature is over 50 degrees then print 
      Controller1.Screen.setCursor(1,1);
      if(drivetemp >= 50)
      {
        Controller1.Screen.print("drive overheat: %f°C", drivetemp);
      }
      Controller1.Screen.setCursor(2,1);
      if(rolltemp >= 50)
      {
        Controller1.Screen.print("roller overheat: %f°C", rolltemp);
      }
      if(catatemp >= 50)
      {
        Controller1.Screen.print("cata  overheat: %f°C", catatemp);
      }
    }
    if(printtime)
    {
       autoend = Brain.Timer.time(sec);
    }
    autotime = autoend - autostart;
    printf("currentx: %.4f, currenty: %.4f, heading: %.4f, auto time: %.4f, leftpower: %.4f, rightpower: %.4f ytrack: %f xtrack: %f\n", 
    currx, curry, currheaddeg, autotime, catalimit.angle(), br.voltage(), ytrack.position(deg)*2.75*M_PI/360,xtrack.position(deg)*2.75*M_PI/360);
    Controller1.Screen.print(currheaddeg);
    wait(100, msec);
  }
}

//function for resetting all drive motor encoder values 
void drivereset()
{
  fl.resetPosition();
  fr.resetPosition();
  ml.resetPosition();
  mr.resetPosition();
  bl.resetPosition();
  br.resetPosition();
}

//stops drive immediately 
void drivestop()
{
  fl.stop();
  fr.stop();
  ml.stop();
  mr.stop();
  bl.stop();
  br.stop();
}

//resets both tracking wheels at the start of match 
void trackreset()
{
  xtrack.resetRotation();
  ytrack.resetRotation();
}

//calculates motor power using PD loop
double motorpower(double currerror, double preverror, float kP, float kI, float kD)
{
  sumerror += currerror;
  double power1 = kP * currerror + kI * sumerror + kD * (currerror - preverror); //PD loop calculation
  return power1;
}