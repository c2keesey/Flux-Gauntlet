#ifndef EFFECTHELPERS_H
#define EFFECTHELPERS_H

#include <FastLED.h>

// Clear the virtual LED array
void clearVleds(CRGB *vleds);

// Helper for drawPrecise
CRGB ColorFraction(CRGB colorIn, float fraction);

// Draw a segment that appears to move between LEDs in vleds.
void drawPrecise(float fPos, float len, CRGB color, CRGB *vleds);

// Outputs a random number in the range [-x, -y], [y, x]
float randomAbsRange(float x, float y);

// Outputs a random number +/- a percentage of the number
float randomVariance(float number, float variancePercent);

#endif // EFFECTHELPERS_H
