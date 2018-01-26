#pragma once

#include <inttypes.h>

// initialise timer(s) here
void initMotors();

// control the motor-power, pay attention to the direction of rotation
void setMotors(int8_t left, int8_t right);

// you may use this to set Motor-DDRs
void deactivateMotors();

void activateMotors();