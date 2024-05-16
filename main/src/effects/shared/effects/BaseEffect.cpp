#include <FastLED.h>
#include "BaseEffect.h"
#include "../EffectHelpers.h"

BaseEffect::BaseEffect(ColorPalette *palette, u8_t rotPalSpread) : palette(palette), originalPalette(palette), rotPalSpread(rotPalSpread)
{
    rotationPalette = new ColorPalette(std::vector<CHSV>{CHSV(0, 255, 255)}, rotPalSpread, 10, 10);
}

BaseEffect::~BaseEffect()
{
    delete rotationPalette;
}

void BaseEffect::triggerWrite()
{
    if (millis() - lastTrigger >= getTriggerDelay())
    {
        if (lastTriggerState)
        {
            isHeld = true;
        }
        trigger();
        lastTrigger = millis();
        lastTriggerState = true;
    }
}

unsigned long BaseEffect::getTriggerDelay()
{
    if (isHeld)
    {
        return minUpdatePeriod;
    }
    else
    {
        return triggerDelay;
    }
}

void BaseEffect::release()
{
    lastTriggerState = false;
    isHeld = false;
}

void BaseEffect::draw()
{
    update();
}

CHSV *BaseEffect::getVleds()
{
    return vleds;
}

void BaseEffect::setPalette(ColorPalette pal)
{
    palette = &pal;
}

void BaseEffect::setRotationPalette()
{
    palette = rotationPalette;
}

void BaseEffect::rotatePalette(int index)
{
    rotationPalette->rotate(index);
}

void BaseEffect::reset()
{
    palette = originalPalette;
    clearVleds(vleds);
}

void BaseEffect::updateVleds(int index, CHSV color)
{
    if (index < 0 || index >= NUM_LEDS)
    {
        return;
    }
    vleds[index] = color;
}

bool BaseEffect::isEffectActive()
{
    return isActive;
}

// int getUpdatePeriod()
// {
//     if (fps > minFpsThreshold)
//     {
//         return minUpdatePeriod;
//     }

//     // Exponential halfLife
//     int updatePeriod = minUpdatePeriod + (maxUpdatePeriod - minUpdatePeriod) * exp(-k * fps);

//     return updatePeriod;
// }
