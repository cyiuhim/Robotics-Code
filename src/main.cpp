#include "main.h"
#include "../include/definitions/drivecontrols.hpp"
#include "../include/definitions/devices.hpp"

#include "../include/definitions/auton.hpp"
#include "../include/definitions/init.hpp"

void on_center_button() {
	static bool pressed = false;
	pressed = !pressed;
	if (pressed) {
		pros::lcd::set_text(2, "I was pressed!");
	} else {
		pros::lcd::clear_line(2);
	}
}
int brainDisplay() {
	while (true) {
		pros::lcd::print(0, "rotation: %f", currentheading);
		tracks = tr.get_value();
		pros::lcd::print(1, "track: %f", tracks);
	  pros::lcd::print(3, "track error: %f", trackerror[0]);
		delay(10);
	}
	return 1;
}

void initialize() {
	pros::lcd::initialize();
	pros::Task brainStuff(brainDisplay);
	setbrake();
	calibrate();
}


void disabled() {}


void competition_initialize()
{
	setbrake();
	calibrate();
}


void autonomous()
{
	mainauto(1, 1);
}


void opcontrol()
{

	while(true)
	{
			drivercontrols();
			pros::delay(20);
	}


}
