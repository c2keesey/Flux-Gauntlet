#include "g_EffectsHandler.h"

#include <FastLED.h>
#include <stdexcept>
#include "../shared/EffectLibrary.h"
#include "../../config/config.h"
#include "../shared/effects/FireworkShow.h"
#include "g_effects/controlEffects/ControlRing.h"
#include "g_effects/controlEffects/ButtonSelect.h"
#include "g_effects/controlEffects/SelectRing.h"
#include "g_effects/Pew.h"
#include "g_effects/Flash.h"
#include "g_effects/Blast.h"

extern CRGB leds[];
extern bool *effectButtons[];
extern bool auxButtonPressed;
extern EffectLibrary effectLibrary;

g_EffectsHandler::g_EffectsHandler()
{
    activeEffects.resize(NUM_EFFECT_BUTTONS, nullptr);

    activeEffects[PRIMARY_BUTTON] = effectLibrary.getPreset(PRIMARY_BUTTON, curPreset);
    activeEffects[SECONDARY_BUTTON] = effectLibrary.getPreset(SECONDARY_BUTTON, curPreset);
    activeEffects[SPEC_BUTTON] = effectLibrary.getPreset(SPEC_BUTTON, curPreset);

    modeChangeEffect = new ControlRing();
    buttonSelectEffect = new ButtonSelect();
    effectSelectEffect = new SelectRing();
}

g_EffectsHandler::~g_EffectsHandler()
{
    for (BaseEffect *effect : activeEffects)
    {
        delete effect;
    }
    activeEffects.clear();

    delete modeChangeEffect;
    delete buttonSelectEffect;
    delete effectSelectEffect;
}

BaseEffect *g_EffectsHandler::getEffect(size_t index)
{
    if (index >= activeEffects.size())
    {
        throw std::out_of_range("Index is out of bounds for the activeEffects vector.");
    }
    return activeEffects[index];
}

size_t g_EffectsHandler::getEffectCount() const
{
    return activeEffects.size();
}

void g_EffectsHandler::handleButtonPress()
{
    // if (suppress)
    // {
    //     return;
    // }
    for (int buttonNumber = 0; buttonNumber < NUM_EFFECT_BUTTONS; buttonNumber++)
    {
        if (effectButtons[buttonNumber] != nullptr && *effectButtons[buttonNumber] == true)
        {
            *effectButtons[buttonNumber] = false;

            if (activeEffects[buttonNumber] != nullptr)
            {
                activeEffects[buttonNumber]->triggerWrite();
            }
        }
    }
}

void g_EffectsHandler::triggerControl(unsigned long holdTime)
{
    modeChangeEffect->setHoldTime(holdTime);
    if (std::find(activeEffects.begin(), activeEffects.end(), modeChangeEffect) == activeEffects.end())
    {
        activeEffects.push_back(modeChangeEffect);
    }

    modeChangeEffect->triggerWrite();
}

void g_EffectsHandler::cancelControl()
{
    auto it = std::find(activeEffects.begin(), activeEffects.end(), modeChangeEffect);
    if (it != activeEffects.end())
    {
        modeChangeEffect->cancel();
        activeEffects.erase(it);
        delete *it;
    }
}

void g_EffectsHandler::triggerModeChange(int mode)
{
    if (mode == SET_MODE)
    {
        // suppressEffects();
        addEffect(buttonSelectEffect);
    }
    else if (mode == EFFECT_MODE)
    {
        // unsuppressEffects();
        buttonSelectEffect->reset();
        removeEffect(buttonSelectEffect);
        effectSelectEffect->reset();
        removeEffect(effectSelectEffect);
    }
}

/**
 * In initial SET_MODE, selects the button to select effect for.
 *
 * @param button button to select effect for
 *
 */
void g_EffectsHandler::selectButton(EffectButton button)
{
    try
    {
        Serial.println("Selecting button");
        buttonSelectEffect->setButton(button);
        addEffect(effectSelectEffect);
    }
    catch (...)
    {
        Serial.println("Error selecting button");
    }
}

void g_EffectsHandler::addEffect(BaseEffect *effect)
{
    if (std::find(activeEffects.begin(), activeEffects.end(), effect) == activeEffects.end())
    {
        activeEffects.push_back(effect);
    }
}

void g_EffectsHandler::removeEffect(BaseEffect *effect)
{
    auto it = std::find(activeEffects.begin(), activeEffects.end(), effect);
    if (it != activeEffects.end())
    {
        activeEffects.erase(it);
        delete *it;
    }
}

// void g_EffectsHandler::suppressEffects()
// {
//     suppress = true;
// }

// void g_EffectsHandler::unsuppressEffects()
// {
//     suppress = false;
// }

void g_EffectsHandler::selectEffect(EffectButton button, int encoderPos)
{

    int effectIndex = getEffectSelectIndex(button, encoderPos);
    delete activeEffects[button];
    activeEffects[button] = effectLibrary.getEffect(button, effectIndex);
    effectSelectEffect->setEffect(effectIndex, effectLibrary.getNumEffects(button));
}

int g_EffectsHandler::getEffectSelectIndex(EffectButton button, int encoderPos)
{
    int numEffects = 1;
    int pos = (encoderPos / 2) % numEffects;
    if (pos < 0)
    {
        pos += numEffects;
    }
    return pos;
}