#ifndef EFFECTSHANDLER_H
#define EFFECTSHANDLER_H

#include "effects/BaseEffect.h"

extern bool *effectButtons[];

class EffectsHandler
{
protected:
    virtual BaseEffect *getEffect(size_t index) = 0;
    virtual size_t getEffectCount() const = 0;

public:
    EffectsHandler();

    virtual void setupEffectLibrary() = 0;
    virtual void drawFrame();

private:
    CRGB getLed(size_t index0);
};

#endif // EFFECTSHANDLER_H
