#line 1 "/Users/c2k/ArduinoProjects/LEDARMv2/main/EffectsHandler.h"
#ifndef EFFECTSHANDLER_H
#define EFFECTSHANDLER_H

#include <Arduino.h>
#include <FastLED.h>

#include "effects/BaseEffect.h"
#include "effects/SolidEncoder.h"
#include "config.h"

extern CRGB leds[];

class EffectsHandler {
private:
    BaseEffect* effects[3] = {nullptr, nullptr, nullptr};

public:
    EffectsHandler() {
        effects[0] = new SolidEncoder(leds, NUM_LEDS);
    }

    ~EffectsHandler() {
        for (auto& effect : effects) {
            delete effect;
        }
    }

    void updateEffect(int effectNumber, BaseEffect* effect) {
        if (effectNumber >= 0 && effectNumber < 3) {
            delete effects[effectNumber];
            effects[effectNumber] = effect;
        }
    }

    void drawFrame() {
        for (auto& effect : effects) {
            if (effect != nullptr) {
                effect->draw();
            }
        }
        FastLED.show();
    }
};

#endif // EFFECTSHANDLER_H
