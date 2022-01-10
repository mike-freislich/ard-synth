#ifndef IM_BUTTON_H
#define IM_BUTTON_H

#include "IMControl.h"

class IMButton: public IMControl
{

private:
    int buttonState;
    int lastButtonState = HIGH;
    uint32_t debounceDelay = 50;
    uint32_t lastDebounceTime = 0;
    void (*onButtonPressed)(void);

public:

    // Constructor
    IMButton(int pin, void (*callback)(void) = NULL, int btnPinMode = INPUT_PULLUP)
    :IMControl(pin, btnPinMode)
    {        
        onButtonPressed = callback;        
    }

    // Destructor
    ~IMButton() {}

    void update()
    {
        int reading = digitalRead(pin);

        if (reading != lastButtonState)
            lastDebounceTime = millis();

        if (millis() - lastDebounceTime > debounceDelay)
        {
            if (reading != buttonState) {
                buttonState = reading;

            if (buttonState == LOW && onButtonPressed)
                onButtonPressed();
            }
            
        }

        lastButtonState = reading;
    }

    bool isPressed()
    {
        return buttonState == LOW;
    }
};

#endif
