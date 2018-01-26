include "MotorControl.h"

#include <FrameStream.h>
#include <Frameiterator.h>
#include <avr/io.h>

/* Function forward declaration*/
void deactivateMotors();

void activateMotors();
/* Global vars */

/* Functions */

void initMotors() {
    TCCR4D &= ~_BV(WGM41);
    TCCR4D &= ~_BV(WGM40);

    TCCR4B |= _BV(CS40);// Prescaler x1
    TCCR4B &= ~_BV(CS41);
    TCCR4B &= ~_BV(CS42);
    TCCR4B &= ~_BV(CS43);

    TCCR4A &= ~_BV(COM4B1);   // Set phase correct timer M2
    TCCR4A |= _BV(COM4B0);
    TCCR4A |= _BV(PWM4B);// Enable
    TCCR4C &= ~_BV(COM4D1);   // Set phase correct timer M1
    TCCR4C |= _BV(COM4D0);
    TCCR4C |= _BV(PWM4D);// Enable
}

void setMotors(int8_t left, int8_t right) {
    OCR4B = 127 + (left * -1);
    OCR4D = 127 + right;
}

void setVelocityMotors(float left, float right) {
    setMotors(left * 127 / 0.6, right * 127 / 0.6);
}

void deactivateMotors() {
    // set input mode
    DDRB &= ~_BV(PB5);
    DDRB &= ~_BV(PB6);
    DDRD &= ~_BV(PD6);
    DDRD &= ~_BV(PD7);
}

void activateMotors() {
    // set output mode
    DDRB |= _BV(PB5);
    DDRB |= _BV(PB6);
    DDRD |= _BV(PD6);
    DDRD |= _BV(PD7);
}