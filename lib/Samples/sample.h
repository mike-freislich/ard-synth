#ifndef SAMPLE_H
#define SAMPLE_H
#include <Arduino.h>

#define a4 440
#define SAMPLERATE 100000

uint16_t getSamples(byte* &data)
{
    return sizeof(data);
}

// sample position at number of ticks
uint16_t getSampleAtTick(byte* &data, uint16_t ticks)
{
    return 1;
}

double getFrequency(byte forNote)
{
  byte octave = forNote / 12;
  byte semitone = forNote - 12.0 * octave;
  double octA = a4 * pow(2, (octave - 4));
  double f = octA * pow(2, ((semitone - 9) / 12.0));
  return f;
}

double ticksPerCycle(int Hz, long sampleRate = SAMPLERATE)
{
  return sampleRate / Hz;
}


#endif