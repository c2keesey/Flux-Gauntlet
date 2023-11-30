#line 1 "/Users/c2k/ArduinoProjects/LEDARMv2/main/effects/SolidEncoder.h"
// SolidEncoder.h

#ifndef SOLIDENCODER_H
#define SOLIDENCODER_H

#include "BaseEffect.h"

extern volatile int encoderPos;

class SolidEncoder : public BaseEffect
{
public:
    SolidEncoder(CRGB *ledsArray, int numLeds) : BaseEffect(ledsArray, numLeds) {}
    void draw() override
    {
        FastLED.clear();
        for (int i = 0; i < numLeds; i++)
        {
            leds[i] = CHSV((i + encoderPos) % 255, 255, 255);
        }
        FastLED.show();
    }
};
#endif // SOLIDENCODER_H