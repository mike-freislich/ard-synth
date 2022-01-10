#ifndef IM_POT_H
#define IM_POT_H

#include "IMControl.h"

class IMPot: public IMControl
{
private:    
    uint32_t value = 0;
    void (*onValueChanged)(uint32_t reading);
    byte tolerance = 10;

public:
    // Constructor
    IMPot(uint32_t pin, void (*callback)(uint32_t reading) = NULL, uint32_t potPinMode = INPUT)
    : IMControl(pin, potPinMode)
    {
        analogReadResolution(10);
        onValueChanged = callback;     
    }

    // Destructor
    ~IMPot() {}

    void update() {  
        uint32_t reading = analogRead(pin);                
        if (abs((int)reading - (int)value) > tolerance) {
            value = reading;
            onValueChanged(value);
        }
    }

    void setTolerance(byte tolerance) { this->tolerance = tolerance; }

    uint32_t getValue() { return value; }
};

#endif