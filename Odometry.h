#pragma once


#include <avr/io.h>
#include <avr/interrupt.h>

#include <inttypes.h>

//Arduino.h has some Pi
#include <Arduino.h>



struct OdomData
{
    volatile int32_t left;
    volatile int32_t right;
};

struct VelocityData
{
    float left;
    float right;
};


//initialises Odometrie
void initOdom();

//writes count courrent of ticks to structure
void odomTicks(struct OdomData&);

VelocityData getVelocityData();