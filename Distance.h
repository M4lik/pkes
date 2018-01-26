#ifndef ESSIRSENSOR_H
#define ESSIRSENSOR_H

#include <inttypes.h>


void configADC();

uint16_t linearizeSR(uint16_t);

uint16_t linearizeLR(uint16_t);

int16_t readADC(uint8_t);

uint16_t getDistance();

uint32_t getMeanDistance();


#endif