#ifndef EFFECTHELPERS_H
#define EFFECTHELPERS_H

#include <FastLED.h>

void clearVleds(CRGB *vleds);
CRGB ColorFraction(CRGB colorIn, float fraction);
void drawPrecise(float fPos, float len, CRGB color, CRGB *vleds);

#endif // EFFECTHELPERS_H
