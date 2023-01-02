#include "main.h"
#include "../include/definitions/devices.hpp"
#include "../include/definitions/drivecontrols.hpp"
#include "../include/definitions/drivetrain.hpp"
#include "../include/definitions/intake.hpp"
#include "../include/definitions/uptake.hpp"

using namespace pros;
double leftx, lefty, rightx, righty;
int r1, r2, l1, a, b;

Drivetrain driver;
Intake intakes;
Uptake uptakes;

void setabrake()
{
  fl.set_brake_mode(E_MOTOR_BRAKE_BRAKE);
  fr.set_brake_mode(E_MOTOR_BRAKE_BRAKE);
  bl.set_brake_mode(E_MOTOR_BRAKE_BRAKE);
  br.set_brake_mode(E_MOTOR_BRAKE_BRAKE);
}

void setbbrake()
{
  fl.set_brake_mode(E_MOTOR_BRAKE_COAST);
  fr.set_brake_mode(E_MOTOR_BRAKE_COAST);
  bl.set_brake_mode(E_MOTOR_BRAKE_COAST);
  br.set_brake_mode(E_MOTOR_BRAKE_COAST);
}

void drivercontrols()
{
  leftx = master.get_analog(E_CONTROLLER_ANALOG_LEFT_X);
  lefty = master.get_analog(E_CONTROLLER_ANALOG_LEFT_Y);
  driver.drive(lefty, leftx);

  righty = master.get_analog(E_CONTROLLER_ANALOG_RIGHT_Y);
  l1 = master.get_digital(E_CONTROLLER_DIGITAL_L1);
  r1 = master.get_digital(E_CONTROLLER_DIGITAL_R1);
  r2 = master.get_digital(E_CONTROLLER_DIGITAL_R2);
  a = master.get_digital(E_CONTROLLER_DIGITAL_A);
  b = master.get_digital(E_CONTROLLER_DIGITAL_B);

  if(l1 != 1)
  {
    uptakes.muptake(r1, r2);
    intakes.mintake(righty);
  }
  else
  {
    uptakes.indexing(r1, r2);
  }

  if(a == 1)
  {
    setabrake();
  }
  if(b == 1)
  {
    setbbrake();
  }
}
