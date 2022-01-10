#include "main.h"

HardwareTimer audioClock = HardwareTimer(TIM2);

// wavetype storage:
// 0 is pulse
// 1 is triangle
// 2 is saw
// 3 is sine
byte shape = 3; // initialize as sine
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
  setupPins();
  userButton = new IMButton(USER_BTN, &onButtonPressed);

  samplerate = SAMPLERATE;

  // initialize variables
  frequency = analogRead(POT_FREQ); // initialize frequency
  freqscaled = frequency + 1;       // from 1 to ~50,000 period = samplerate/freqscaled;

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

void setupPins()
{
  //pinMode(LED_BUILTIN, OUTPUT);
  pinMode(USER_BTN, INPUT);
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
      triInc = 1;

    sawInc = 255 / period;
    if (sawInc == 0)
      sawInc = 1;
    sinInc = 20000 / period;
  }
}

void checkPW()
{
  PWCurrent = analogRead(POT_PULSE);
  PWCurrent = 512;
  if (abs(PWCurrent - pulseWidth) > PWTolerance)
  {                         // if reading from pot exceeds tolerance
    pulseWidth = PWCurrent; // new pulse width, val between 0 and 1023
    pulseWidthScaled = int(pulseWidth / 1023 * period);
  }
}

void checkShape()
{
}

void audioClock_Tick()
{
  // increment t and reset each time it reaches period
  t += 1;
  if (t >= period)
    t = 0;
  switch (shape)
  {
  case 0: // pulse
    if (pulseWidthScaled <= t)
      wave = 255;
    else
      wave = 0;
    break;
  case 1: // triangle
    if ((period - t) > t)
      if (t == 0)
        triByte = 0;
      else
        triByte += triInc;
    else
      triByte -= triInc;
    if (triByte > 255)
      triByte = 255;
    else if (triByte < 0)
      triByte = 0;
    wave = triByte;
    break;
  case 2: // saw
    if (t = 0)
      sawByte = 0;
    else
      sawByte += sawInc;
    wave = sawByte;
    break;
  case 3: // sine
    sinNum = t * sinInc;
    wave = pgm_read_byte_near(sine20000 + sinNum);
    break;
  }

  GPIOB->ODR = wave;
}

void onButtonPressed() {
  rtt.println("user button pressed");
}

void loop()
{
  userButton->update();
  
  rtt.printf("updating userbutton %d\n", userButton->isPressed());
  checkFreq();
  checkShape();
  checkPW();
  delay(10);
  // digitalWrite(LED_BUILTIN, HIGH);
  // delay(1000);
  // digitalWrite(LED_BUILTIN, LOW);
  //  STM_PORT(PortA) = 1 << shape;

  // PortB = 1<<shape; //TODO : implement LEDs
  //rtt.printf("f=%d p=%d w=%d\n", freqCurrent, pulseWidthScaled, typecurrent);
}
