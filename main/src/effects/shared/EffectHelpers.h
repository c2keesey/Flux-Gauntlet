#ifndef EFFECTHELPERS_H
#define EFFECTHELPERS_H

#include <FastLED.h>

const CHSV BLACK(0, 0, 0);

// Clear the virtual LED array
void clearVleds(CHSV *vleds);

// Helper for drawPrecise
CHSV colorFraction(CHSV colorIn, float fraction);

// Draw a segment that appears to move between LEDs in vleds.
void drawPrecise(float fPos, float len, CHSV color, CHSV *vleds);

// Outputs a random number in the range [-x, -y], [y, x]
float randomAbsRange(float x, float y);

// Outputs a random number +/- a percentage of the number
float randomVariance(float number, float variancePercent);

// Inverse scale a uint8_t value for speed and period timing
int inverseScale(uint8_t value, int min, int max);

#endif // EFFECTHELPERS_H
