#include "main.h"
#include "../../include/definitions/intake.hpp"
#include "../../include/definitions/devices.hpp"
using namespace pros;

void Intake::mintake(double velocity)
{
  li = velocity;
  ri = velocity;
}
