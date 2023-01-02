#include "main.h"
#include "../../include/definitions/uptake.hpp"
#include "../../include/definitions/intake.hpp"

#include "../../include/definitions/devices.hpp"
using namespace pros;

void Uptake::muptake(int up, int down)
{
  if(up == 1 && down != 1)
  {
    bu = 100;
    tu = 100;
  }
  else if(down == 1&& up != 1)
  {
    bu = -100;
    tu = -100;
  }
  else
  {
    bu = 0;
    tu = 0;
  }
}


void Uptake::indexing(int up, int down)
{
  righty = master.get_analog(E_CONTROLLER_ANALOG_RIGHT_Y);
  if(up == 1 && down != 1)
  {
    bu = 100;
    tu = 100;
    li = righty;
    ri = righty;
  }
  else if(down == 1&& up != 1)
  {
    bu = -100;
    tu = -100;
    li = righty;
    ri = righty;
  }
  else
  {
    bu = 80;
    tu = -40;
    li = 100;
    ri = 100;
  }
}
