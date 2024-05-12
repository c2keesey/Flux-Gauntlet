#include <FastLED.h>
#include "BaseEffect.h"

BaseEffect::BaseEffect(ColorPalette palette) : palette(palette)
{
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
    palette = pal;
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
