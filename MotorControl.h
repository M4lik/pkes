#pragma once

#include <inttypes.h>

void initMotors();

void setMotors(int8_t left, int8_t right);

void updateMotors();

// set the Velocity of both motor in m/s
void setVelocityMotors(float left, float right);

// these functions start and stop the automatic motor activation
void activateMotors();

void deactivateMotors();