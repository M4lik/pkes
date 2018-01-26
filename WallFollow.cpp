#include "Odometry.h"
#include "PID.h"
#include "MotorControl.h"
#include "Distance.h"

short state = 5;
short counter = 0;
uint16_t dtickscurr = 0;
uint16_t dticksgoal = 0;
bool rotating = false;
uint16_t aticksgoal = 0;
float shortestDistance = 0;
uint16_t shortestDistanceTicks = 0;
uint16_t ticksBeforeRotation = 0;

extern uint16_t sumOfTicks;

void rotation(int16_t a) {
    ticksBeforeRotation = sumOfTicks;
    aticksgoal = sumOfTicks + a;
    rotating = true;
}

bool isDoneRotating() {
    if (aticksgoal <= sumOfTicks) {
        rotating = false;
        return true;
    } else {
        VelocityData vD = getVelocityValues(0.2, -0.2);
        setVelocityMotors(vD.left, vD.right);
        return false;
    }
}

void findWall() {
    if (!rotating) {
        rotation(floor(360 * 3.4));
    }
    if (shortestDistance > getMeanDistance()) {
        shortestDistance = getMeanDistance();
        shortestDistanceTicks = sumOfTicks - ticksBeforeRotation;
    }
    if (isDoneRotating()) {
        Serial.println("IS DONE ROTATING");
        state = 4;
    }
}

void turnWall() {
    if (!rotating) rotation(shortestDistanceTicks);
    if (isDoneRotating()) {
        \tstate = 3;
    }
}

void driveDist(float d) {
    dticksgoal = sumOfTicks + d * 2195;
    dtickscurr = sumOfTicks;
}

void wait() {
    if (counter < 10) {
        counter++;
        VelocityData vD = getVelocityValues(0, 0);
        setVelocityMotors(vD.left, vD.right);
    } else {
        counter = 0;
        state = 5;
        driveDist(0.2);
    }
}


bool distDriven() {
    if (dticksgoal <= sumOfTicks) {
        return true;
    } else {
        VelocityData vD = getVelocityValues(0.15, 0.15);
        setVelocityMotors(vD.left, vD.right);
        return false;
    }
}

void drive() {
    VelocityData vD = getVelocityValues(0.3, 0.3);
    setVelocityMotors(vD.left, vD.right);
    activateMotors();
    if (distDriven() || getMeanDistance() <= 100) {
        state = 1;
    }
}

void parallelize() {
    if (!rotating)
        rotation(90 * 2.944);
    if (isDoneRotating()) {
        state = 4;
    }
}

void motorMain() {
    if (state == 1) findWall();
    if (state == 2) turnWall();
    if (state == 3) parallelize();
    if (state == 4) wait();
    if (state == 5) drive();
}