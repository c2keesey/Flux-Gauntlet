#ifndef BASEEFFECT_H
#define BASEEFFECT_H

#include <FastLED.h>
#include "../../config/config.h"

extern double fps;

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
    int speed;

public:
    BaseEffect(CRGBPalette256 palette = RainbowColors_p);
    virtual void trigger() = 0;
    void triggerWrite();
    virtual void update() = 0;
    virtual void draw();

    CRGB *getVleds();
    void setPalette(CRGBPalette256 pal);
    uint8_t getPalNum();
    void setPalNum(uint8_t num);
    void setSpeed(int speed);
};

#endif // BASEEFFECT_H
