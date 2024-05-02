// Rings.h

#ifndef RINGS_H
#define RINGS_H

#include <FastLED.h>

class Rings
{
private:
    int rings[16] = {21, 27, 25, 23, 23, 22, 20, 19, 19, 19, 17, 16, 15, 12, 12, 10};
    int ringsLength = 16;
    int breakpoints[17] = {0};
    CRGB *vleds;

public:
    Rings(CRGB *vleds) : vleds(vleds)
    {
        for (int i = 0; i < ringsLength; i++)
        {
            breakpoints[i + 1] = breakpoints[i] + rings[i];
        }
    }

    int getRingsLength()
    {
        return ringsLength;
    }

    void drawRing(int ringi, CRGB color)
    {
        for (int i = breakpoints[ringi]; i < breakpoints[ringi + 1]; i++)
        {
            vleds[i] = color;
        }
    }
    int getRingStart(int ringi)
    {
        return breakpoints[ringi];
    }
    int getRingEnd(int ringi)
    {
        return breakpoints[ringi + 1];
    }
    int getRingFromIndex(int index)
    {
        for (int i = 0; i < ringsLength; i++)
        {
            if (index >= breakpoints[i] && index < breakpoints[i + 1])
            {
                return i;
            }
        }
        return -1;
    }
    int getRingLength(int ringi)
    {
        return rings[ringi];
    }
};
#endif // RINGS_H