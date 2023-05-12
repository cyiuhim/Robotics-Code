//defining autonomous functions 

#ifndef autonomous_h
#define autonomous_h

extern int automode; //which auton it is running 
extern double autostart; //the point of time at which auton starts
extern int drivemode, catamode, rollermode; //which mode the auton threads are running for drive, cata and roller
extern bool catapiston; //shoot using how many piston boosts
extern double rollerspeed; //roller speed, variable for auton
extern int turndir; //1 = turning right, -1 = turning left 

//pid variables below: 
extern double currdriveerror, prevdriveerror, currturnerror, prevturnerror; 
//current and previous drive and turn errors
extern double sumerror; //sum of errors for ki
extern float drivemultiply;
extern double lpidpower, rpidpower; //left and right drive pid power
extern double leftpower, rightpower; //left and right drive motor outputs 
extern double maxaccel, accel; //acceleration constant and max power due to gradual acceleration
extern int loopnumber; //number of pid loops run since start of each movement 
extern double maxpower; //maximum power that the drive power can run
extern double goal; //goal distance or heading 
extern double starttime, stoptime; //start and end time of a pid movement 

//odom variables below: 
extern double xheading, yheading; //x and y components of vector from current coordinates to goal coordinates
extern double fullbearing, reducedbearing; //the actual bearing and reduced bearing of vector using trig
extern double inertialbearing, inertialbackbearing; 
//the bearing for the inertial sensor that counts clockwise, starts from 0 degrees at positive y axis, facing with front/back
extern double goalheading, adjustheading; 
//goal heading of the vector on the inertial scale, adjusting to be the closest to the current heading 
extern double goaldistance; //distance between current point and goal 

class autoTask
{
  public: 

  static void driving();
  //drivetrain thread during autonomous
  static void cataing();
  //catapult thread during autonomous
  static void rolling();
  //roller thread during autonomous
  static void mainauto();
  //main autonomous function that is running during autonomous, based on automode

  //driving functions: 
  
  static void fwdrevpid();
  //pid control loop for assigning motor output when driving forward or backward
  static void turnpid();
  //pid loop for turning right/left
  static double calcheading(double startx, double starty, double endx, double endy);
  //calculates closest heading to face a certain point from one point 
  static double calcbackheading(double startx, double starty, double endx, double endy);

  //cata functions: 
  static void shoot(bool piston);
  //shoot the cata, using how many piston boosts


  //roller functions:


  //user functions: 
  static void shoot();
  static void shootpiston();
  //shoot using 0/2 piston boosts
  static void turn(double goalheading1, double time);
  //turn to a certain heading, within a time limit
  static void drive(double drivedis, double time);
  //drive by a certain distance within a time limit
  static void driveshoot(double drivedis, double drivemul, double time1, double time2);
  //shoot while driving 
  static void driveintake(double drivedis, double time1, double time2);
  //drop intake while driving 
  static void turntopoint(double goalx, double goaly, double time);
  //turn until front is facing goal point
  static void turntopointback(double goalx, double goaly, double time);
  //turn until back is facing goal point
  static void drivetopoint(double goalx, double goaly, double time);
  static void drivetopointback(double goalx, double goaly, double time);
  //drive for distance between current point and goal point, forward/backward
  static void gotopoint(double goalx, double goaly, double turntime, double drivetime);
  static void gotopointback(double goalx, double goaly, double turntime, double drivetime);
  //turn then drive to goal point, facing forward/backward
  static void rollerdeg(double roller, double rollertime);
  //spins the roller by a number of degrees, within a time limit

  //main auton functions: 
  static void testing();
  //for testing and tuning pid, odom 
  static void awp();
  //8 disc, 2 rollers
  static void leftauto();
  //9 discs, 1 roller
  static void rightauto();
  //9 discs, 1 roller
  static void skills();
  //(idk how many discs yet)
};

#endif