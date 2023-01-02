#ifndef auton_hpp
#define auton_hpp

#define drivedelay 45
#define drivedelaytime 10 // in ms
#define turndelay 15
#define turndelaytime 30 // in ms
#define driveaccel 8
void mainauto(int automode, int calibrate);
extern double trackerror[drivedelay];
extern double track, tracks;
extern float drivekP, turnkP;
extern float leftdrivekD, leftturnkD, rightdrivekD, rightturnkD;
extern float gyroturnkP, gyroturnkD;
extern double starttime, currenttime, timecount;
extern double goal, previousheading, currentheading;
extern double headingerror[turndelay];
extern double maxaccel;
extern int loopexit, loopnumber;
/*
current heading error is position 0 of array
previous heading error is position 1 of array
then it keeps going for the rest of the array
each pid loop the values in the array shift by one position to the right, and the last one is deleted
the first one is calculating how much the robot is off, using normal heading calculations
*/
class Auton
{
public:
void drive(double setpoint, double maxpower, int direction, double maxerror, double timelimit);

void driveindexing(double driveinches, int intakevelocity, double maxpower, double maxerror, int intake, int uptake, double timelimit);

int motorpower(double error, double previouserror, float kP, float kD);

//void turn(double setpoint, double maxpower, int direction, double maxerror, double timelimit);

void gyroturn(double setpoint, double maxpower, int direction, double maxerror, double timelimit);

void gyroturnto(double setpoint, double maxpower, int direction, double maxerror, double timelimit);

void uptake(double uptakedegrees, double uptakevelocity, double timelimit);

void uptake1(double uptakedegrees, double uptakevelocity, double timelimit);


void downtake(double uptakedegrees, double uptakevelocity, double timelimit);

void motormove(double leftvel, double rightvel, double invel, double botvel, double topvel, int drivestop, int intakestop, int upstop, int time);

double min(double value1, double value2, double value3);

void drivestop();

void intakestop();

void uptakestop();

void drivereset();

void uptakereset();

void trackreset();

void screenclear();


};
#endif
