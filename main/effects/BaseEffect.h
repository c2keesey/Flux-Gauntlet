// BaseEffect.h

#ifndef BASEEFFECT_H
#define BASEEFFECT_H

#include <FastLED.h>
#include "config.h"

class BaseEffect
{
protected:
    CRGB vleds[NUM_LEDS] = {0};
    unsigned long lastTrigger = 0;
    int triggerDelay = 100;
    CRGBPalette256 palette;
    uint8_t curPalNum = 0;

public:
    BaseEffect(CRGBPalette256 palette = RainbowColors_p)
        : palette(palette)
    {
    }
    virtual void draw() = 0;
    virtual void trigger() = 0;
    void triggerWrite()
    {
        if (millis() - lastTrigger >= triggerDelay)
        {
            trigger();
            lastTrigger = millis();
        }
    }
    CRGB *getVleds()
    {
        return vleds;
    }
    void setPalette(CRGBPalette256 pal)
    {
        palette = pal;
    }
    uint8_t getPalNum()
    {
        return curPalNum;
    }
    void setPalNum(uint8_t num)
    {
        curPalNum = num;
    }
};

#endif // BASEEFFECT_H
