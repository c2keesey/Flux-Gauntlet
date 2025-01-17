#ifndef EFFECTSHANDLER_H
#define EFFECTSHANDLER_H

#include "effects/BaseEffect.h"

class EffectsHandler
{
protected:
    virtual BaseEffect *getEffect(size_t index) = 0;
    virtual size_t getEffectCount() const = 0;

public:
    EffectsHandler();

    virtual void drawFrame();

private:
    CRGB getLed(size_t index0);
};

#endif // EFFECTSHANDLER_H
