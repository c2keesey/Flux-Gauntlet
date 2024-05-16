#ifndef g_EFFECTSHANDLER_H
#define g_EFFECTSHANDLER_H

#include "../shared/EffectLibrary.h"
#include "../../config/config.h"
#include "../shared/EffectsHandler.h"
#include "g_effects/controlEffects/ControlRing.h"
#include "g_effects/controlEffects/ButtonSelect.h"
#include "g_effects/controlEffects/SelectRing.h"
#include <vector>
#include "../../control/Button.h"
#include "g_effects/controlEffects/PaletteRing.h"

class g_EffectsHandler : public EffectsHandler
{
private:
    std::vector<BaseEffect *> activeEffects;
    ControlRing *modeChangeEffect; // TODO: abstract to control parent class
    ButtonSelect *buttonSelectEffect;
    SelectRing *effectSelectEffect;
    PaletteRing *paletteSelectEffect;
    long lastShow = 0;
    unsigned long lastAuxPressedMillis = 0;
    // bool suppress = false;

    Button *effectButtons[NUM_EFFECT_BUTTONS];

protected:
    BaseEffect *getEffect(size_t index) override;
    size_t getEffectCount() const override;
    void addEffect(BaseEffect *effect);
    void removeEffect(BaseEffect *effect);

public:
    g_EffectsHandler();
    ~g_EffectsHandler();

    void init();

    void drawFrame() override;
    void handleButtonPress();
    void triggerControl(unsigned long holdTime);
    void cancelControl();
    void setSetMode(bool isSet);
    void triggerEffectMode();
    void triggerButtonSelectMode();
    void selectButton(ButtonEnum button);
    void selectEffect(ButtonEnum button, int effectIndex);
    void selectPalette(ButtonEnum button, int effectIndex);
    int getSelectIndex(int numEffects, int encoderPos);
    void triggerPresetSelectMode();
    void selectPreset(int encoderPos);
    void selectEffectMode();
    void selectPaletteMode();
    void resetEffects();

    // void suppressEffects();
    // void unsuppressEffects();
};

#endif // g_EFFECTSHANDLER_H
