#ifndef g_EFFECTSHANDLER_H
#define g_EFFECTSHANDLER_H

#include "../shared/EffectLibrary.h"
#include "../../config/config.h"
#include "../shared/EffectsHandler.h"
#include "g_effects/ControlRing.h"
#include <vector>

class g_EffectsHandler : public EffectsHandler
{
private:
    std::vector<BaseEffect *> activeEffects;
    ControlRing *controlEffect; // TODO: abstract to control parent class
    EffectLibrary effectLibrary;
    int preset = ACTION_PRESET;
    long lastShow = 0;
    unsigned long lastAuxPressedMillis = 0;

protected:
    BaseEffect *getEffect(size_t index) override;
    size_t getEffectCount() const override;
    void setupEffectLibrary() override;

public:
    g_EffectsHandler();

    void handleButtonPress();
    void triggerControl(unsigned long holdTime);
    void cancelControl();
    void rotatePreset();
    void changeColor(int buttonNumber);
};

#endif // g_EFFECTSHANDLER_H
