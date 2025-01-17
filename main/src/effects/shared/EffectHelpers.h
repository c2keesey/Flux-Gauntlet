#ifndef EFFECTHELPERS_H
#define EFFECTHELPERS_H

#include <FastLED.h>

const CHSV BLACK(0, 0, 0);

// Clear the virtual LED array
void clearVleds(CHSV *vleds);

// Helper for drawPrecise
CHSV colorFraction(CHSV colorIn, float fraction, u8_t floor);

// Draw a segment that appears to move between LEDs in vleds.
void drawPrecise(float fPos, float len, CHSV color, CHSV *vleds, u8_t floor = 0);

// Outputs a random number in the range [-x, -y], [y, x]
float randomAbsRange(float x, float y);

// Outputs a random number +/- a percentage of the number
float randomVariance(float number, float variancePercent);

// Inverse scale a uint8_t value for speed and period timing
int inverseScale(uint8_t value, int min, int max);

// Random float between 0 and 1 with high precision
float RandomFloat();

// Fade a color by a fraction
CRGB colorFractionRGB(CRGB colorIn, float fraction);

// Draw a segment that appears to move between LEDs in vleds.
void drawPreciseRGB(float fPos, float count, CRGB color, CRGB *vleds);

// Convert a temperature value to a color using HSV
CHSV HeatColorHSV(uint8_t temperature);

#endif // EFFECTHELPERS_H
