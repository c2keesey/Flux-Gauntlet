#ifndef g_EFFECTSHANDLER_H
#define g_EFFECTSHANDLER_H

#include "../shared/EffectLibrary.h"
#include "../../config/config.h"
#include "../shared/EffectsHandler.h"

class g_EffectsHandler : public EffectsHandler
{
private:
    BaseEffect *activeEffects[NUM_EFFECT_BUTTONS] = {};
    EffectLibrary effectLibrary;
    int preset = ACTION_PRESET;
    long lastShow = 0;

protected:
    BaseEffect *getEffect(size_t index) override;
    size_t getEffectCount() const override;
    void setupEffectLibrary() override;

public:
    g_EffectsHandler();

    void handleButtonPress();
    void rotatePreset();
    void changeColor(int buttonNumber);
};

#endif // g_EFFECTSHANDLER_H
