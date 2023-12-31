#include "g_EffectsHandler.h"

#include <FastLED.h>

#include "../shared/EffectLibrary.h"
#include "../../config/config.h"
#include "../shared/effects/FireworkShow.h"

extern CRGB leds[];
extern bool *effectButtons[];
extern bool auxButtonPressed;

g_EffectsHandler::g_EffectsHandler()
{
    setupEffectLibrary();
    activeEffects[PRIMARY_BUTTON] = effectLibrary.getEffect(preset, PRIMARY_BUTTON);
    activeEffects[SECONDARY_BUTTON] = effectLibrary.getEffect(preset, SECONDARY_BUTTON);
    activeEffects[SPEC_BUTTON] = effectLibrary.getEffect(preset, SPEC_BUTTON);

    // activeEffects[SECONDARY_BUTTON] = new FireworkShow();
}

BaseEffect *g_EffectsHandler::getEffect(size_t index)
{
    return activeEffects[index];
}

size_t g_EffectsHandler::getEffectCount() const
{
    return NUM_EFFECT_BUTTONS;
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

void g_EffectsHandler::rotatePreset()
{
    // TODO: move to a type of active effect
    for (int i = 0; i < preset + 1; i++)
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