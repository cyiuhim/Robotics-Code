#include "main.h"
#include "../../include/definitions/drivetrain.hpp"
#include "../../include/definitions/devices.hpp"
using namespace pros;
double fwpow, turnpow;
double leftpower, rightpower;
void Drivetrain::drive(double fw, double turn)
{
  fwpow = fw;
  turnpow = turn * 0.85;
  leftpower = fwpow + turnpow;
  rightpower = fwpow - turnpow;
  fl = leftpower;
  bl = leftpower;
  fr = rightpower;
  br = rightpower;
}
