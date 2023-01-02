#include "main.h"
#include "../../include/definitions/devices.hpp"
using namespace pros;

Controller master(E_CONTROLLER_MASTER); //controller

Motor fl(11, E_MOTOR_GEARSET_18, true, E_MOTOR_ENCODER_DEGREES); //frontleft
Motor fr(20, E_MOTOR_GEARSET_18, false, E_MOTOR_ENCODER_DEGREES); //frontright
Motor bl(13, E_MOTOR_GEARSET_18, true, E_MOTOR_ENCODER_DEGREES); //backleft
Motor br(18, E_MOTOR_GEARSET_18, false, E_MOTOR_ENCODER_DEGREES); //backright
Motor bu(16, E_MOTOR_GEARSET_36, false, E_MOTOR_ENCODER_DEGREES); //bottomuptake
Motor tu(10, E_MOTOR_GEARSET_18, true, E_MOTOR_ENCODER_DEGREES); //topuptake
Motor li(4, E_MOTOR_GEARSET_18, false, E_MOTOR_ENCODER_DEGREES); //leftintake
Motor ri(15, E_MOTOR_GEARSET_18, true, E_MOTOR_ENCODER_DEGREES); //rightintake
Imu in(14);
ADIEncoder tr('G', 'H', true);
