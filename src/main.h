#include <Arduino.h>
#include "RTTStream.h"
#include "PinMappings.h"
#include "IMButton.h"
#include "IMPot.h"
#include "waves.h"
#include "sample.h"

void setupPins();
void audioClock_Tick();
void onButtonPressed();
void onFrequencyChanged(uint32_t freq);
void onPulseWidthChanged(uint32_t width);

RTTStream rtt;
IMButton *btnShape;
IMPot *potFreq;
IMPot *potWidth;

enum WAVETYPE {PULSE = 0, TRIANGLE, SAW, SINE};

byte shape = WAVETYPE::SINE; // initialize as sine
byte typecurrent = 8;
byte typelast;
byte typecounter[4];

// variables for PW pot monitoring
float pulseWidth;
int pulseWidthScaled;
int PWCurrent;
byte PWTolerance = 20; // adjust this to increase/decrease stability of PW measurement

// variables for freq pot monitoring
int frequency;
int freqCurrent;
byte freqTolerance = 20; // adjust this to increase/decrease stability of frequency measurement
unsigned int freqscaled;

byte wave;
long t;
long samplerate;
long period;

// storage variables- I used these to cut down on the math being performed during the interrupt
int sawByte = 0;
byte sawInc;
int triByte = 0;
byte triInc;
int sinNum = 0;
int sinInc;
