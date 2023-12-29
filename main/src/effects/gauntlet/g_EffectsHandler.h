#ifndef g_EFFECTSHANDLER_H
#define g_EFFECTSHANDLER_H

#include <Arduino.h>
#include <FastLED.h>
#include "../shared/EffectLibrary.h"
#include "../../config/config.h"

extern CRGB leds[];
extern bool *effectButtons[];

class g_EffectsHandler
{
private:
    BaseEffect *activeEffects[NUM_EFFECT_BUTTONS] = {nullptr, nullptr, nullptr};
    EffectLibrary effectLibrary;
    int preset = 3;
    long lastShow = 0;

public:
    g_EffectsHandler();

    void handleButtonPress();
    void rotatePreset();
    void changeColor(int buttonNumber);
    void drawFrame();
};

#endif // g_EFFECTSHANDLER_H
