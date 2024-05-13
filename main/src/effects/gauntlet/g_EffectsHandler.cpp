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
#include "../../control/Button.h"

extern CRGB leds[];

extern Button thumbButton;
extern Button indexButton;
extern Button middleButton;
extern Button ringfButton;
extern Button pinkyButton;

extern EffectLibrary effectLibrary;

#include "g_effects/Casimir.h"

g_EffectsHandler::g_EffectsHandler()
{
    activeEffects.resize(NUM_EFFECT_BUTTONS, nullptr);
}

void g_EffectsHandler::init()
{
    effectButtons[MIDDLE] = &middleButton;
    effectButtons[RINGF] = &ringfButton;
    effectButtons[THUMB] = &thumbButton;
    effectButtons[INDEX] = &indexButton;
    effectButtons[PINKY] = &pinkyButton;

    activeEffects[MIDDLE] = effectLibrary.getEffect(MIDDLE, 0);
    activeEffects[RINGF] = effectLibrary.getEffect(RINGF, 0);
    activeEffects[THUMB] = effectLibrary.getEffect(THUMB, 0);
    activeEffects[INDEX] = effectLibrary.getEffect(INDEX, 0);
    activeEffects[PINKY] = effectLibrary.getEffect(PINKY, 0);

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
    for (Button *button : effectButtons)
    {
        if (button->isPressed())
        {
            if (activeEffects[button->getEnumVal()] != nullptr)
            {
                activeEffects[button->getEnumVal()]->triggerWrite();
            }
        }
        else
        {
            if (activeEffects[button->getEnumVal()] != nullptr)
            {
                activeEffects[button->getEnumVal()]->release();
            }
        }
    }
}

void g_EffectsHandler::triggerControl(unsigned long holdTime)
{
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

void g_EffectsHandler::setSetMode(bool isSet)
{
    modeChangeEffect->setMode(isSet);
}

void g_EffectsHandler::triggerButtonSelectMode()
{
    // suppressEffects();
    addEffect(buttonSelectEffect);
    setSetMode(true);
}

void g_EffectsHandler::triggerEffectMode()
{
    // unsuppressEffects();
    // modeChangeEffect->cancel(); TODO: fix bug where it wont trigger again
    buttonSelectEffect->reset();
    removeEffect(buttonSelectEffect);
    effectSelectEffect->reset();
    removeEffect(effectSelectEffect);
    setSetMode(true);
}

/**
 * In initial SET_MODE, selects the button to select effect for.
 *
 * @param button button to select effect for
 *
 */
void g_EffectsHandler::selectButton(ButtonEnum button)
{
    buttonSelectEffect->setButton(button);
    addEffect(effectSelectEffect);
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

void g_EffectsHandler::selectEffect(ButtonEnum button, int encoderPos)
{
    int numEffects = effectLibrary.getNumEffects(button);
    int effectIndex = getSelectIndex(numEffects, encoderPos);
    activeEffects[button] = effectLibrary.getEffect(button, effectIndex);
    effectSelectEffect->setEffect(effectIndex, numEffects);
}

int g_EffectsHandler::getSelectIndex(int numEffects, int encoderPos)
{

    int pos = (encoderPos / 2) % numEffects;
    if (pos < 0)
    {
        pos += numEffects;
    }
    return pos;
}

void g_EffectsHandler::triggerPresetSelectMode()
{
    addEffect(effectSelectEffect);
}

void g_EffectsHandler::selectPreset(int encoderPos)
{
    int numPresets = effectLibrary.getNumPresets();
    int presetIndex = getSelectIndex(numPresets, encoderPos);
    activeEffects[MIDDLE] = effectLibrary.getPresetFromI(MIDDLE, presetIndex);
    activeEffects[RINGF] = effectLibrary.getPresetFromI(RINGF, presetIndex);
    activeEffects[THUMB] = effectLibrary.getPresetFromI(THUMB, presetIndex);
    activeEffects[INDEX] = effectLibrary.getPresetFromI(INDEX, presetIndex);
    activeEffects[PINKY] = effectLibrary.getPresetFromI(PINKY, presetIndex);
    effectSelectEffect->setEffect(presetIndex, numPresets);
}

void g_EffectsHandler::drawFrame()
{
    FastLED.clear(false);

    // Draw active effects
    for (BaseEffect *effect : activeEffects)
    {
        if (effect != nullptr && effect->isEffectActive())
        {
            effect->draw();
        }
    }

    // Combine effect colors
    for (BaseEffect *effect : activeEffects)
    {
        if (effect != nullptr && effect->isEffectActive())
        {
            CHSV *copyArray = effect->getVleds();
            if (copyArray != nullptr)
            {
                for (int j = 0; j < NUM_LEDS; j++)
                {
                    leds[j] += copyArray[j];
                }
            }
        }
    }

    // Limit LED brightness
    for (int i = 0; i < NUM_LEDS; i++)
    {
        leds[i].r = min(leds[i].r, (uint8_t)255);
        leds[i].g = min(leds[i].g, (uint8_t)255);
        leds[i].b = min(leds[i].b, (uint8_t)255);
    }

    FastLED.show();
}