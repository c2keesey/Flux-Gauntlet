#include <FastLED.h>
#include "BaseEffect.h"

BaseEffect::BaseEffect(CRGBPalette256 palette) : palette(palette)
{
}
void BaseEffect::triggerWrite()
{
    if (millis() - lastTrigger >= triggerDelay)
    {
        trigger();
        lastTrigger = millis();
    }
}
void BaseEffect::draw()
{
    update();
}

CHSV *BaseEffect::getVleds()
{
    return vleds;
}

void BaseEffect::setPalette(CRGBPalette256 pal)
{
    palette = pal;
}
uint8_t BaseEffect::getPalNum()
{
    return curPalNum;
}
void BaseEffect::setPalNum(uint8_t num)
{
    curPalNum = num;
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
