#include "Distance.h"
#include <Arduino.h>
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

extern uint32_t distances[];


/**
 * @brief Configures the ADC related to mode, clock speed, gain
 *        resolution and refrence voltage
 *
 *
 * chose the reference voltage carfully related to the output
 * range of the sensor.
 */
void configADC() {
    ADCSRA |= (1 << ADEN); //Enable ADC
    ADMUX |= (1 << REFS0); //Reference voltage 3300mv

}

/**
 * @brief Starts a single conversion and receives a result return in mV
 */
int16_t readADC(uint8_t channel) {
    //Select input
    if (channel > 0) ADMUX |= (1 << MUX0);
    else ADMUX &= ~(1 << MUX0);

    //Manual trigger
    ADCSRA |= (1 << ADSC);
    //Wait for conversion
    _delay_us(1);

    int16_t mV;

    // mV = (ADCH*4*3.226);//*4 --> 8-bit, *3,226 --> V input
    mV = (ADCL + 256 * ADCH) * 3.226;

    return mV;
}

/**
 * @brief Maps the digital voltage information on a distance
 *        in mm
 */
uint16_t linearizeSR(uint16_t distmV) {
    if (distmV > 3000) return 0; //too close
    if (distmV < 600) return 0; //too far away
    return LookupShort[(int) floor((distmV - 600) / 100)]; //LookUp

}

/**
 * @brief Maps the digital voltage information on a distance
 *        in mm
 */
uint16_t linearizeLR(uint16_t distmV) {
    if (distmV > 2700) return 0; //too close
    if (distmV < 1000) return 0; //too far away
    return LookupLong[(int) floor((distmV - 1000) / 100)];

}

uint16_t getDistance() {   //"Better" distances
    uint16_t val0 = linearizeLR(readADC(0));
    uint16_t val1 = linearizeSR(readADC(1));

    if (val0 == 0 || val1 == 0) return val1 + val0;

    return (uint16_t) (val0 + val1) / 2;


}

uint32_t getMeanDistance() {
    uint32_t result = 0;
    for (int i = 0; i < 100; i++) {
        result += distances[i] / 100;
    }
    return result;
}