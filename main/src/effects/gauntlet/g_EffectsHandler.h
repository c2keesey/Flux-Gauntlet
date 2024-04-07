#ifndef g_EFFECTSHANDLER_H
#define g_EFFECTSHANDLER_H

#include "../shared/EffectLibrary.h"
#include "../../config/config.h"
#include "../shared/EffectsHandler.h"
#include "g_effects/controlEffects/ControlRing.h"
#include "g_effects/controlEffects/ButtonSelect.h"
#include "g_effects/controlEffects/SelectRing.h"
#include <vector>

class g_EffectsHandler : public EffectsHandler
{
private:
    std::vector<BaseEffect *> activeEffects;
    ControlRing *modeChangeEffect; // TODO: abstract to control parent class
    ButtonSelect *buttonSelectEffect;
    SelectRing *effectSelectEffect;
    Preset curPreset = Preset::ACTION;
    long lastShow = 0;
    unsigned long lastAuxPressedMillis = 0;
    // bool suppress = false;

protected:
    BaseEffect *getEffect(size_t index) override;
    size_t getEffectCount() const override;
    void addEffect(BaseEffect *effect);
    void removeEffect(BaseEffect *effect);

public:
    g_EffectsHandler();

    void handleButtonPress();
    void triggerControl(unsigned long holdTime);
    void cancelControl();
    void triggerModeChange(int mode);
    void rotatePreset();
    void changeColor(int buttonNumber);
    void selectButton(EffectButton button);
    void selectEffect(EffectButton button, int effectIndex);
    int getEffectSelectIndex(EffectButton button, int encoderPos);
    // void suppressEffects();
    // void unsuppressEffects();
};

#endif // g_EFFECTSHANDLER_H
