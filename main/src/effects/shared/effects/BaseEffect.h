#ifndef BASEEFFECT_H
#define BASEEFFECT_H

#include <FastLED.h>
#include "../../../config/config.h"
#include "../ColorPalette.h"
#include "../ColorPaletteInstances.h"

extern double fps;

// TODO: Make CHSV
struct Beam
{
    float pos;
    CHSV color;
};

class BaseEffect
{
protected:
    // Each effect has its own virtual LED array
    CHSV vleds[NUM_LEDS] = {CHSV(0, 0, 0)};
    unsigned long lastTrigger = 0;
    ColorPalette *palette;
    ColorPalette *rotationPalette;
    ColorPalette *originalPalette;
    uint8_t curPalNum = 0;
    unsigned long prevMillis = 0;
    int speed;
    unsigned long triggerDelay = 150; // Hold time until minUpdatePeriod
    unsigned long minUpdatePeriod = 20;
    bool lastTriggerState = false;
    bool isHeld = false;
    bool isActive = true;

public:
    u8_t rotPalSpread;

    BaseEffect(ColorPalette *pal = &rainbow_cp, u8_t rotPalSpread = 15);
    ~BaseEffect();
    virtual void trigger() = 0;
    unsigned long getTriggerDelay();
    void release();
    void triggerWrite();
    virtual void update() = 0;
    virtual void draw();

    CHSV *getVleds();

    void setPalette(ColorPalette pal);
    void setRotationPalette();
    void rotatePalette(int index);
    void reset();

    virtual bool isEffectActive();

    // Safely update vleds avoiding out of bounds
    void updateVleds(int index, CHSV color);
};

#endif // BASEEFFECT_H
