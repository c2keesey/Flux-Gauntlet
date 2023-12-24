#ifndef EFFECTSHANDLER_H
#define EFFECTSHANDLER_H

#include <Arduino.h>
#include <FastLED.h>
#include "EffectLibrary.h"
#include "config.h"

extern CRGB leds[];
extern bool *effectButtons[];

class EffectsHandler
{
private:
    BaseEffect *activeEffects[NUM_EFFECT_BUTTONS] = {nullptr, nullptr, nullptr};
    EffectLibrary effectLibrary;
    int preset = 3;
    long lastShow = 0;

public:
    EffectsHandler();

    void handleButtonPress();
    void rotatePreset();
    void changeColor(int buttonNumber);
    void drawFrame();
};

#endif // EFFECTSHANDLER_H
