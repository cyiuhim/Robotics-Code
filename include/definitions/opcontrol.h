//define all driver control functions

#ifndef opcontrol_h
#define opcontrol_h

extern bool a, b, x, y, l1, l2, r1, r2; //variables for the buttons if they are pressed
extern double leftx, lefty, rightx, righty; 
extern int intakeno;

class driveTask
{
  public: 

  static void drivet(); 
  //drive train thread, during driver control period
  static void catat();
  //catapult thread, during driver control
  static void rollt();
  //roller thread, during driver control
  static void expandt();
  //expansion thread, during driver control

  static void drivemotor(double forward, double turn);
  //controls the drive motors, using the input from the arcade drive
  static void rollermotor(double roller);
  //input from right y stick, controls roller motor 
  static void intakelift(bool intake1);
  //controls whether intake lift is up or down
  static void catamotor(bool reload);
  //input from shoot button, controls cata motor to shoot and reload
};
#endif