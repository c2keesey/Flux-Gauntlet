// SolidEncoder.h

#ifndef SOLIDENCODER_H
#define SOLIDENCODER_H

#include "../shared/BaseEffect.h"

extern volatile int encoderPos;

class SolidEncoder : public BaseEffect
{
protected:
    uint8_t priority = 3; // TODO: move to consts file LOW_PRIORITY

public:
    SolidEncoder(CRGB *ledsArray, int numLeds) : BaseEffect(ledsArray, numLeds) {}
    void draw() override
    {
        for (int i = 0; i < numLeds; i++)
        {
            vleds[i] = CHSV((i + encoderPos) % 255, 255, 255);
        }
    }
};
#endif // SOLIDENCODER_H