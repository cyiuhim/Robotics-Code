#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
controller Controller1 = controller(primary);
motor FrontLeft = motor(PORT4, ratio18_1, false);
motor FrontRight = motor(PORT3, ratio18_1, false);
motor LeftIntake = motor(PORT2, ratio18_1, false);
motor RightIntake = motor(PORT9, ratio18_1, false);
motor Lift = motor(PORT8, ratio36_1, false);
motor IntakeArm = motor(PORT6, ratio36_1, false);
motor BackLeft = motor(PORT20, ratio18_1, false);
motor BackRight = motor(PORT12, ratio18_1, false);

// VEXcode generated functions
// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Text.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}