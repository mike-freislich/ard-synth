#include <Arduino.h>
#include <math.h>
#include "sample.h"
#include "waves.h"

#define a4 440
#define SAMPLERATE 100000

void setup()
{
  Serial.begin(115200);
  //for (byte i=0; i<8; i++)
  //  pinMode(i, OUTPUT);
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
  Serial.print("Hz: ");
  Serial.print(freq);
  Serial.print("\tticks ");
  Serial.println(ticks);
  delay(500);    

    
/*
  for (byte b=0; b<8; b++){    
    if ((((byte)data) >> (b)) & 0x01)
      digitalWrite(b, HIGH);
    else
      digitalWrite(b, LOW);
    
  }
*/

}