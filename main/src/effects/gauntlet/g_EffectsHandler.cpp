#include "g_EffectsHandler.h"

#include <Arduino.h>
#include <FastLED.h>

#include "../shared/EffectLibrary.h"
#include "../../config/config.h"

extern CRGB leds[];
extern bool *effectButtons[];

g_EffectsHandler::g_EffectsHandler()
{
    activeEffects[PRIMARY_BUTTON] = effectLibrary.getEffect(1, SPEC_BUTTON);
    activeEffects[PRIMARY_BUTTON]->trigger();
    activeEffects[SECONDARY_BUTTON] = effectLibrary.getEffect(preset, SECONDARY_BUTTON);
    activeEffects[SPEC_BUTTON] = effectLibrary.getEffect(preset, SPEC_BUTTON);
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
    if (preset == 0)
    {
        leds[NUM_LEDS - 14] = CRGB::Purple;
    }
    else if (preset == 1)
    {
        leds[NUM_LEDS - 13] = CRGB::Green;
        leds[NUM_LEDS - 15] = CRGB::Green;
    }
    else
    {
        leds[NUM_LEDS - 12] = CRGB::Red;
        leds[NUM_LEDS - 14] = CRGB::Red;
        leds[NUM_LEDS - 16] = CRGB::Red;
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

void g_EffectsHandler::drawFrame()
{
    for (auto &effect : activeEffects)
    {
        if (effect != nullptr)
        {
            effect->draw();
        }
    }
    FastLED.clear(false);
    for (auto &effect : activeEffects)
    {
        if (effect != nullptr)
        {
            CRGB *copyArray = effect->getVleds();
            for (int i = 0; i < NUM_LEDS; i++)
            {
                leds[i] += copyArray[i];
            }
        }
    }
    for (int i = 0; i < NUM_LEDS; i++)
    {
        if (leds[i].r > 255)
            leds[i].r = 255;
        if (leds[i].g > 255)
            leds[i].g = 255;
        if (leds[i].b > 255)
            leds[i].b = 255;
    }
    FastLED.show();
}
