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
// extern EffectLibrary effectLibrary;

g_EffectsHandler::g_EffectsHandler()
{
    activeEffects.resize(NUM_EFFECT_BUTTONS, nullptr);

    // activeEffects[PRIMARY_BUTTON] = effectLibrary.getPreset(PRIMARY_BUTTON, curPreset);
    // activeEffects[SECONDARY_BUTTON] = effectLibrary.getPreset(SECONDARY_BUTTON, curPreset);
    // activeEffects[SPEC_BUTTON] = effectLibrary.getPreset(SPEC_BUTTON, curPreset);

    activeEffects[PRIMARY_BUTTON] = new Blast();
    activeEffects[SECONDARY_BUTTON] = new Flash();
    activeEffects[SPEC_BUTTON] = new Blast();

    modeChangeEffect = new ControlRing();
    buttonSelectEffect = new ButtonSelect();
    effectSelectEffect = new SelectRing();
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
    }
}

// void g_EffectsHandler::rotatePreset()
// {
//     // TODO: move to a type of active effect
//     for (int i = 0; i < curPreset; i++)
//     {
//         leds[NUM_LEDS - 14 - i] = CRGB::White;
//     }
//     FastLED.show();

//     curPreset = (curPreset + 1) % NUM_PRESETS;
//     for (int buttonNumber = 0; buttonNumber < NUM_EFFECT_BUTTONS; buttonNumber++)
//     {
//         activeEffects[buttonNumber] = effectLibrary.getEffect(curPreset, buttonNumber);
//     }
// }

// void g_EffectsHandler::changeColor(int buttonNumber)
// {
//     if (activeEffects[buttonNumber] != nullptr)
//     {
//         uint8_t nextPal = activeEffects[buttonNumber]->getPalNum() + 1;
//         activeEffects[buttonNumber]->setPalette(effectLibrary.getPalette(nextPal));
//         activeEffects[buttonNumber]->setPalNum(nextPal);
//     }
// }

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
    // activeEffects[button] = effectLibrary.getEffect(button, effectIndex);
    // effectSelectEffect->setEffect(effectIndex, effectLibrary.getNumEffects(button));

    effectSelectEffect->setEffect(effectIndex, 1);
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