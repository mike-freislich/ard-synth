#include "main.h"

HardwareTimer audioClock = HardwareTimer(TIM2);



void setup()
{
  setupPins();
  userButton = new IMButton(USER_BTN, &onButtonPressed);
  freqPot = new IMPot(POT_FREQ, &onFrequencyChanged);

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
  pinMode(LED_BUILTIN, OUTPUT);
 // pinMode(USER_BTN, INPUT);
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
  shape = (shape + 1)%4;
}

void onFrequencyChanged(uint32_t freq) {
  rtt.printf("freq pot changed %u\n", freq);
  freqCurrent = freq;

  if (abs(freqCurrent - frequency) > freqTolerance)
  {                                  // if reading from pot exceeds tolerance
    frequency = freqCurrent;         // new frequency- number between 0 and 1024
    freqscaled = 1 * frequency + 1; // from 1 to ~50,000
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

void loop()
{  
  
  //rtt.printf("updating userbutton %d\n", userButton->isPressed());
  //checkFreq();

  checkPW();
  //checkShape();

  freqPot->update();
  userButton->update(); 
  
  //delay(10);
  // digitalWrite(LED_BUILTIN, HIGH);
  // delay(1000);
  // digitalWrite(LED_BUILTIN, LOW);
  //  STM_PORT(PortA) = 1 << shape;

  // PortB = 1<<shape; //TODO : implement LEDs
  //rtt.printf("f=%d p=%d shape=%d\n", freqCurrent, pulseWidthScaled, shape);
  if (userButton->isPressed()) {
    digitalWrite(LED_BUILTIN, LOW); } else
  {
    digitalWrite(LED_BUILTIN, HIGH);
  }
}
