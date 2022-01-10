#ifndef IM_CONTROL_H
#define IM_CONTROL_H
#include <Arduino.h>

class IMControl {
protected:
    uint32_t pin;
public:
    IMControl(uint32_t pin, uint32_t controlPinMode) {
        this->pin = pin;
        pinMode(pin, controlPinMode);
    };
    ~IMControl(){}

    virtual void update() {};
};

#endif