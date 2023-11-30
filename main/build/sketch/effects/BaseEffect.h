#line 1 "/Users/c2k/ArduinoProjects/LEDARMv2/main/effects/BaseEffect.h"
// BaseEffect.h

#ifndef BASEEFFECT_H
#define BASEEFFECT_H

#include <FastLED.h>
#include "config.h"

class BaseEffect
{
protected:
    CRGB *leds;
    int numLeds;

public:
    BaseEffect(CRGB *ledsArray, int numLeds) : leds(ledsArray), numLeds(numLeds) {}
    virtual void draw() = 0;
};

#endif // BASEEFFECT_H
