// BaseEffect.h

#ifndef BASEEFFECT_H
#define BASEEFFECT_H

#include <FastLED.h>
#include "../config.h"

struct Beam
{
    float pos;
    CRGB color;
};

class BaseEffect
{
protected:
    CRGB vleds[NUM_LEDS] = {0};
    unsigned long lastTrigger = 0;
    int triggerDelay = 100;
    CRGBPalette256 palette;
    uint8_t curPalNum = 0;
    unsigned long prevMillis = 0;

    // Update rate
    int minUpdatePeriod = 1;
    int maxUpdatePeriod = 500;
    int minFpsThreshold = 50;
    double k = 0.1; // Decay constant

public:
    BaseEffect(CRGBPalette256 palette = RainbowColors_p)
        : palette(palette)
    {
    }
    virtual void trigger() = 0;
    void triggerWrite()
    {
        if (millis() - lastTrigger >= triggerDelay)
        {
            trigger();
            lastTrigger = millis();
        }
    }
    virtual void update(){};
    virtual void draw()
    {
        if (millis() - prevMillis > getUpdateRate())
        {
            prevMillis = millis();
            update();
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
    int getUpdateRate()
    {
        uint16_t fps = FastLED.getFPS();
        if (fps > minFpsThreshold)
        {
            return minUpdatePeriod;
        }

        // Exponential decay
        int updatePeriod = minUpdatePeriod + (maxUpdatePeriod - minUpdatePeriod) * exp(-k * fps);

        return updatePeriod;
    }
};

#endif // BASEEFFECT_H
