#include "g_EffectsHandler.h"

#include <FastLED.h>
#include <stdexcept>
#include "../shared/EffectLibrary.h"
#include "../../config/config.h"
#include "../shared/effects/FireworkShow.h"
#include "g_effects/ControlRing.h"

extern CRGB leds[];
extern bool *effectButtons[];
extern bool auxButtonPressed;

g_EffectsHandler::g_EffectsHandler()
{
    setupEffectLibrary();
    // Resize the vector to accommodate the necessary elements.
    activeEffects.resize(NUM_EFFECT_BUTTONS, nullptr);

    // Now you can directly assign effects to the specific buttons.
    activeEffects[PRIMARY_BUTTON] = effectLibrary.getEffect(preset, PRIMARY_BUTTON);
    activeEffects[SECONDARY_BUTTON] = effectLibrary.getEffect(preset, SECONDARY_BUTTON);
    activeEffects[SPEC_BUTTON] = effectLibrary.getEffect(preset, SPEC_BUTTON);

    controlEffect = new ControlRing(DEFAULT_PALETTE);
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

void g_EffectsHandler::setupEffectLibrary()
{
}

void g_EffectsHandler::handleButtonPress()
{
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
    controlEffect->setHoldTime(holdTime);
    if (std::find(activeEffects.begin(), activeEffects.end(), controlEffect) == activeEffects.end())
    {
        activeEffects.push_back(controlEffect);
    }
    controlEffect->triggerWrite();
}

void g_EffectsHandler::cancelControl()
{
    auto it = std::find(activeEffects.begin(), activeEffects.end(), controlEffect);
    if (it != activeEffects.end())
    {
        controlEffect->cancel();
        activeEffects.erase(it);
    }
}

void g_EffectsHandler::rotatePreset()
{
    // TODO: move to a type of active effect
    for (int i = 0; i < preset; i++)
    {
        leds[NUM_LEDS - 14 - i] = CRGB::White;
    }
    FastLED.show();

    preset = (preset + 1) % NUM_PRESETS;
    for (int buttonNumber = 0; buttonNumber < NUM_EFFECT_BUTTONS; buttonNumber++)
    {
        activeEffects[buttonNumber] = effectLibrary.getEffect(preset, buttonNumber);
    }
}

void g_EffectsHandler::changeColor(int buttonNumber)
{
    if (activeEffects[buttonNumber] != nullptr)
    {
        uint8_t nextPal = activeEffects[buttonNumber]->getPalNum() + 1;
        activeEffects[buttonNumber]->setPalette(effectLibrary.getPalette(nextPal));
        activeEffects[buttonNumber]->setPalNum(nextPal);
    }
}