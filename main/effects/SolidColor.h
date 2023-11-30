// SolidColor.h

#ifndef SOLIDCOLOR_H
#define SOLIDCOLOR_H

#include "BaseEffect.h"

class SolidColor : public BaseEffect
{
protected:
    uint8_t priority = 4;
    CRGB color;

public:
    SolidColor(CRGB *ledsArray, int numLeds, const CRGB &solidColor)
        : BaseEffect(ledsArray, numLeds), color(solidColor) {}

    void draw() override
    {
        fill_solid(vleds, numLeds, color);
    }
};

#endif // SOLIDCOLOR_H
