#include <FastLED.h>
#include "../../config/config.h"
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
    if (millis() - prevMillis > 1)
    {
        prevMillis = millis();
        update();
    }
}

CRGB *BaseEffect::getVleds()
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
// int getUpdatePeriod()
// {
//     if (fps > minFpsThreshold)
//     {
//         return minUpdatePeriod;
//     }

//     // Exponential decay
//     int updatePeriod = minUpdatePeriod + (maxUpdatePeriod - minUpdatePeriod) * exp(-k * fps);

//     return updatePeriod;
// }

void BaseEffect::setSpeed(int speed)
{
    this->speed = speed;
}
