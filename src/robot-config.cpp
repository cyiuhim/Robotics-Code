//initializing ports for all motors and triports 

#include "vex.h"

using namespace vex;

//cata = front, fl/fr = top, ml/mr = bottom
brain Brain;
controller Controller1 = controller(primary);
motor fl = motor(PORT1, ratio6_1, false);
motor ml = motor(PORT16, ratio6_1, true); 
motor bl = motor(PORT2, ratio6_1, true); 
motor fr = motor(PORT8, ratio6_1, true);
motor mr = motor(PORT9, ratio6_1, false);
motor br = motor(PORT7, ratio6_1, false);
//front motors have opposite direction from the rest of left/right side 
motor cata = motor(PORT15, ratio36_1, false);
motor roller = motor(PORT13, ratio6_1, true);
rotation catalimit = rotation(PORT17);
inertial in1 = inertial(PORT18);

encoder ytrack = encoder(Brain.ThreeWirePort.E);
encoder xtrack = encoder(Brain.ThreeWirePort.C);
pneumatics boost = pneumatics(Brain.ThreeWirePort.A);

pneumatics expand1 = pneumatics(Brain.ThreeWirePort.B); 
pneumatics expand2 = pneumatics(Brain.ThreeWirePort.G);
pneumatics intake = pneumatics(Brain.ThreeWirePort.H);

void vexcodeInit(void) {
  // Nothing to initialize
}