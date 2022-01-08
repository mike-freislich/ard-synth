#ifndef SAMPLE_H
#define SAMPLE_H
#include <Arduino.h>

uint16_t getSamples(byte* &data)
{
    return sizeof(data);
}

// sample position at number of ticks
uint16_t getSampleAtTick(byte* &data, uint16_t ticks)
{
    return 1;
}


#endif