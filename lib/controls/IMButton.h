#ifndef IM_BUTTON_H
#define IM_BUTTON_H

#include <Arduino.h>

class IMButton
{

private:
    uint32_t pin;
    int buttonState;
    int lastButtonState = LOW;
    uint32_t debounceDelay = 50;
    uint32_t lastDebounceTime = 0;
    void (*onButtonPressed)(void);

public:
    enum BUTTONSTATE
    {
        OFF,
        JUSTPRESSED,
        PRESSED
    };

    // Constructor
    IMButton(int pin, void (*callback)(void) = NULL, int btnPinMode = OUTPUT)
    {
        this->pin = pin;
        onButtonPressed = callback;
        pinMode(pin, btnPinMode);
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
            if (reading != buttonState)
                buttonState = reading;

            if (buttonState == HIGH && onButtonPressed)
                onButtonPressed();
        }
buttonState = reading;
        lastButtonState = reading;
    }

    bool isPressed()
    {
        return buttonState == HIGH;
    }
};

#endif
