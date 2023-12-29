#ifndef EFFECTSHANDLER_H
#define EFFECTSHANDLER_H

#include <vector>
#include "effects/BaseEffect.h"

extern CRGB *leds[];
extern bool *effectButtons[];

class EffectsHandler
{
protected:
    std::vector<BaseEffect *> activeEffects = {};

public:
    EffectsHandler();

    virtual void setupEffectLibrary() = 0;
    void drawFrame();
};

#endif // EFFECTSHANDLER_H
