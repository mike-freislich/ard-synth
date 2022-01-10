#include "main.h"

/*********************************************************
some notes about pin setup:
4 momentary switches control waveshape (analog in 0-3)
   -sine connects to A0
   -triangle A1
   -saw A2
   -pulse A3
freq control pot (log taper) is connected to analog in 4
pulse width modulation pot (linear taper) connected to anolog in 5
PORT D (digital pins 0-7) are 8 bit function out

*********************************************************/

HardwareTimer audioClock = HardwareTimer(TIM2);

// wavetype storage:
// 0 is pulse
// 1 is triangle
// 2 is saw
// 3 is sine
byte type = 3; // initialize as square
byte typecurrent = 8;
byte typelast;
byte typecounter[4];
byte i;

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

void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(DBIT_0, OUTPUT);
  pinMode(DBIT_1, OUTPUT);
  pinMode(DBIT_2, OUTPUT);
  pinMode(DBIT_3, OUTPUT);
  pinMode(DBIT_4, OUTPUT);
  pinMode(DBIT_5, OUTPUT);
  pinMode(DBIT_6, OUTPUT);
  pinMode(DBIT_7, OUTPUT);
  pinMode(BTN_SIN, INPUT);
  pinMode(BTN_SAW, INPUT);
  pinMode(BTN_TRI, INPUT);
  pinMode(BTN_PLS, INPUT);
  pinMode(POT_FREQ, INPUT);
  pinMode(POT_PULSE, INPUT);

  samplerate = 100000;

  // initialize variables
  frequency = analogRead(POT_FREQ);      // initialize frequency
  freqscaled = frequency + 1; // from 1 to ~50,000 period = samplerate/freqscaled;

  pulseWidth = analogRead(POT_PULSE); // initalize pulse width
  pulseWidthScaled = int(pulseWidth / 1023 * period);

  triInc = 511 / period;
  sawInc = 255 / period;
  sinInc = 20000 / period;

  analogReadResolution(10);

  audioClock.setOverflow(samplerate, HERTZ_FORMAT);
  audioClock.attachInterrupt(audioClock_Tick);
  audioClock.resume();
}

void checkFreq()
{
  freqCurrent = analogRead(POT_FREQ);
  //freqCurrent = 128;
  if (abs(freqCurrent - frequency) > freqTolerance)
  {                                  // if reading from pot exceeds tolerance
    frequency = freqCurrent;         // new frequency- number between 0 and 1024
    freqscaled = 10 * frequency + 1; // from 1 to ~50,000
    period = samplerate / freqscaled;
    pulseWidthScaled = int(pulseWidth / 1023 * period);
    triInc = 511 / period;
    if (triInc == 0)
    {
      triInc = 1;
    }
    sawInc = 255 / period;
    if (sawInc == 0)
    {
      sawInc = 1;
    }
    sinInc = 20000 / period;
  }
}

void checkPW()
{
  PWCurrent = analogRead(POT_PULSE);
  //PWCurrent = 512;
  if (abs(PWCurrent - pulseWidth) > PWTolerance)
  {                         // if reading from pot exceeds tolerance
    pulseWidth = PWCurrent; // new pulse width, val between 0 and 1023
    pulseWidthScaled = int(pulseWidth / 1023 * period);
  }
}

void checkShape()
{
  // debounce and check states of buttons
  //  4 momentary switches control waveshape
  //   -pulse connects to A0
  //   -triangle A1
  //   -saw A2
  //   -sine A3
  typelast = typecurrent;

  if (digitalRead(BTN_PLS) == LOW)
  {
    typecurrent = 1;
  }
  else if (digitalRead(BTN_TRI) == LOW)
  {
    typecurrent = 2;
  }
  else if (digitalRead(BTN_SAW) == LOW)
  {
    typecurrent = 4;
  }
  else if (digitalRead(BTN_SIN) == LOW)
  {
    typecurrent = 8;
  }

  typecurrent = 1;

  for (i = 0; i < 4; i++)
  {
    if (i == type)
    {
    }
    else
    {
      if ((typecurrent & (1 << i)) ^ (typelast & (1 << i)))
      { // current diff than prev and debounce
        if ((typecurrent & (1 << i)))
        {           // currently depressed
          type = i; // set wave type
        }
        else
        {
          typecounter[i] = 12; // else set debounce counter to 12
        }
      }
      else if (((typecurrent & (1 << i)) == (typelast & (1 << i))))
      { // if current same as prev and diff than debounce
        if (typecounter[i] > 0 && --typecounter[i] == 0)
        { // decrease debounce counter and check to see if = 0
          if ((typecurrent & (1 << i)))
          { // if debounce counter = 0 toggle debounced state
            type = i;
          }
        }
      }
    }
  }
}

void audioClock_Tick()
{
  // increment t and reset each time it reaches period
  t += 1;
  if (t >= period)
  {
    t = 0;
  }
  switch (type)
  {
  case 0: // pulse
    if (pulseWidthScaled <= t)
    {
      wave = 255;
    }
    else
    {
      wave = 0;
    }
    break;
  case 1: // triangle
    if ((period - t) > t)
    {
      if (t == 0)
      {
        triByte = 0;
      }
      else
      {
        triByte += triInc;
      }
    }
    else
    {
      triByte -= triInc;
    }
    if (triByte > 255)
    {
      triByte = 255;
    }
    else if (triByte < 0)
    {
      triByte = 0;
    }
    wave = triByte;
    break;
  case 2: // saw
    if (t = 0)
    {
      sawByte = 0;
    }
    else
    {
      sawByte += sawInc;
    }
    wave = sawByte;
    break;
  case 3: // sine
    sinNum = t * sinInc;
    wave = pgm_read_byte_near(sine20000 + sinNum);
    break;
  }

  GPIOB->ODR = wave;
}

void loop()
{
  checkFreq();
  checkShape();
  checkPW();
  delay(10);
  // digitalWrite(LED_BUILTIN, HIGH);
  // delay(1000);
  // digitalWrite(LED_BUILTIN, LOW);
  //  STM_PORT(PortA) = 1 << type;

  // PortB = 1<<type; //TODO : implement LEDs
  rtt.printf("f=%d p=%d w=%d\n", freqCurrent, pulseWidthScaled, typecurrent);
}
