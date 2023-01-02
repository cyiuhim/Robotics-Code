#include "main.h"
#include "../include/definitions/devices.hpp"
#include "../include/definitions/init.hpp"

using namespace pros;

void setbrake()
{
  fl.set_brake_mode(E_MOTOR_BRAKE_COAST);
  fr.set_brake_mode(E_MOTOR_BRAKE_COAST);
  bl.set_brake_mode(E_MOTOR_BRAKE_COAST);
  br.set_brake_mode(E_MOTOR_BRAKE_COAST);
  li.set_brake_mode(E_MOTOR_BRAKE_HOLD);
  ri.set_brake_mode(E_MOTOR_BRAKE_HOLD);
  tu.set_brake_mode(E_MOTOR_BRAKE_HOLD);
  bu.set_brake_mode(E_MOTOR_BRAKE_HOLD);
}

void calibrate()
{
  in.reset();
}
