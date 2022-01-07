
#include "main.h"
#include <USBSerial.h>

// Plotted variables must be declared as globals 
double x;
double y;

void setup()
{
  //SerialUSB.begin();
  //Serial.begin(115200);
  
  //for (byte i=0; i<8; i++)
  //  pinMode(i, OUTPUT);
  setupTimers();
}

void setupTimers() {

}

double getFrequency(byte forNote) {
 byte octave = forNote / 12;
 byte semitone = forNote - 12.0 * octave;
 double octA = a4 * pow(2, (octave-4));
 double f = octA * pow(2,((semitone-9)/12.0));
 return f;
}


double ticksPerCycle(int Hz, long sampleRate = SAMPLERATE)
{
  return sampleRate / Hz;
}  

byte currentNote = 0;
void loop()
{ 
  currentNote ++;
  if (currentNote > 110)
    currentNote = 1;    

  double freq = getFrequency(currentNote);
  double ticks = ticksPerCycle(freq);
  //Serial.print("Hz: ");
  //Serial.print(freq);
  //Serial.print("\tticks ");
  //Serial.println(ticks);

   // Update variables with arbitrary sine/cosine data
    x = 10*sin( 2.0*PI*( millis() / 5000.0 ) );
    y = 10*cos( 2.0*PI*( millis() / 5000.0 ) );

  
  delay(500);    

}