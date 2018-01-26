#include "Distance.h"
#include <Arduino.h>
#include <Frameiterator.h>
#include <avr/io.h>
#include <util/delay.h>

uint8_t LookupShort[25] =
        {220, 187, 163, 145, 130,
         115, 107, 97, 90, 83,
         78, 73, 69, 64, 60,
         58, 53, 50, 47, 45,
         43, 40, 39, 37, 35};//3000 mV - 600 mV

uint16_t LookupLong[18] =
        {630, 600, 500, 474, 447,
         420, 396, 372, 348, 324,
         300, 280, 260, 240, 220,
         200, 190, 175};//2700 mV - 1000 mV



uint16_t ADC_mV_Faktor;

/**
 * @brief Configures the ADC related to mode, clock speed, gain
 *        resolution and refrence voltage
 *
 *
 * chose the reference voltage carfully related to the output
 * range of the sensor.
 */
void configADC() {
    ADMUX |= _BV(REFS0);  // Vcc reference
    ADCSRA |= _BV(ADEN);  // Enable
}

/**
 * @brief Starts a single conversion and receives a result return in mV
 */
int16_t readADC(uint8_t channel) {

    if (channel == 0)
        ADMUX &= ~_BV(MUX0);
    else
        ADMUX |= _BV(MUX0);

    ADCSRA |= _BV(ADSC); //trigger measurement
    _delay_us(1);

    int16_t val = ADCL;
    val |= ((uint16_t) ADCH << 8);
    uint16_t mV = (float) val * 3.2258f;
    return val;
}

/**
 * @brief Maps the digital voltage information on a distance
 *        in mm
 */
uint16_t linearizeSR(uint16_t distmV) {
    if (distmV < 600) return 0;
    if (distmV > 3000) return 65000;
    return LookupShort[(int) floor((distmV - 600) / 100)];
}