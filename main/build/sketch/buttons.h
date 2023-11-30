#line 1 "/Users/c2k/ArduinoProjects/LEDARMv2/main/buttons.h"
// buttons.h

#ifndef BUTTONS_H
#define BUTTONS_H

extern volatile bool buttonPressed;

void handleSpecButtonPress()
{
    buttonPressed = true;
}

void handleAuxButtonPress()
{
    buttonPressed = true;
}

void handleSecondaryButtonPress()
{
    buttonPressed = true;
}

void handlePrimaryButtonPress()
{
    buttonPressed = true;
}

void handleEncoderButtonPress()
{
    buttonPressed = true;
}

#endif // BUTTONS_H
