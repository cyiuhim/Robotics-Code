//define all odom functions, and functions for both driver control and autonomous

#ifndef init_h
#define init_h

extern vex::competition competition1;
extern int testswitch; 
//1 = normal, 2 = testing autons 

extern void setcata();
//sets the catapult to the reload position, hitting the limit switch
extern void shootcata();
//shoots the cata
extern void expansion();
//shoots the expansion mechanism 
extern void setbrake(vex::brakeType braking);
//sets the brake mode of all the drive motors
extern void printscreen();
/*prints the robot's information, including the xy coordinates, 
heading, and auton elapsed time on the terminal*/
extern void drivestop();
//sets the drive to stop immediately 
extern void drivereset();
//resets all drive motor encoder values at the start of the match
extern void trackreset();
//resets both tracking wheels rotation
extern double autostart, autoend;
//auton start and end times 
extern bool printtime;
//sets true when auton starts, false when auton ends

extern double drivetemp, catatemp, rolltemp;
//motor temperature, to prevent overheating, limit at 50 degrees Celsius
extern int testswitch;
//whether it is in testing mode or normal driving mode 
extern double reloaduplimit, reloaddownlimit;
//the upper and lower limits of the rotation sensor when the cata is in reload mode, 
extern double shootlimit, catabottomlimit;
//the lower limit when it is shot, and the lowest angle where it reaches

extern double motorpower(double currerror, double preverror, float kP, float kI, float kD);
//calculates motor power using PD loop and current, previous errors for both drive and turn pids

class odometry { //all odometry functions, position tracking and curve turns 
  public: 

  static void updatesensor(); 
  //updates the sensor values 
  static void calcposdiff();
  //calculates the vectors with reference to global heading
  static void globalpos();
  //thread for updating global position of robot
};

extern double currx, curry, prevx, prevy; //current and previous xy coordinates of robot of last update 
extern double currhead, prevhead, currheaddeg; //current, previous heading radians, and current heading degrees 
extern double currxwheel, currywheel, prevxwheel, prevywheel; //current and previous positions of x and y tracking wheels 
extern double xtrackmove, ytrackmove, headingdiff; //changes in x,y tracking wheels, and inertial heading
extern double xchange, ychange; //coordinate change of robot with respect to global heading
extern double deltax, deltay; //coordinate change of robot with respect to current heading
extern double initheading; //initial heading of the robot if it is not parallel with field 


#endif