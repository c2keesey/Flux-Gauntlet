// FIRE_H
#ifndef FIRE_H
#define FIRE_H

#include "../../shared/effects/BaseEffect.h"
#include "../../shared/EffectHelpers.h"

class Fire : public BaseEffect
{
protected:
    int Start;
    int End;
    int Size;
    int Cooling;
    int Sparks;
    int SparkHeight;
    int Sparking; // Threshold for sparking, higher = more sparks
    int DriftSpeed;
    bool bReversed;
    bool bMirrored;

    byte *heat;

    // When diffusing the fire upwards, these control how much to blend in from the cells below (ie: downward neighbors)
    // You can tune these coefficients to control how quickly and smoothly the fire spreads.

    static const byte BlendSelf = 4;
    static const byte BlendNeighbor1 = 5;
    static const byte BlendNeighbor2 = 4;
    static const byte BlendNeighbor3 = 3;
    static const byte BlendNeighbor4 = 2;
    static const byte BlendTotal = (BlendSelf + BlendNeighbor1 + BlendNeighbor2 + BlendNeighbor3 + BlendNeighbor4);

public:
    // Lower sparking -> more flicker.  Higher sparking -> more consistent flame

    Fire(int start, int end, int cooling = 10, int sparking = 50, int sparks = 5, int sparkHeight = 5, int driftPeriod = 20, bool breversed = true, bool bmirrored = true)
        : BaseEffect(),
          Start(start),
          End(end),
          Size(end - start),
          Cooling(cooling),
          Sparks(sparks),
          SparkHeight(sparkHeight),
          Sparking(sparking),
          DriftSpeed(driftPeriod),
          bReversed(breversed),
          bMirrored(bmirrored)
    {
        if (bMirrored)
            Size = Size / 2;

        heat = new byte[Size]{0};
    }

    virtual ~Fire()
    {
        delete[] heat;
    }

    void trigger() override
    {
        for (int i = 0; i < 10; i++)
        {
            int y = Size - 1 - random(15);
            heat[y] = heat[y] + random(160, 255); // This randomly rolls over sometimes of course, and that's essential to the effect
        }
    }

    void update() override
    {
        clearVleds(vleds);

        // First cool each cell by a little bit
        for (int i = 0; i < Size; i++)
            if (random(4) == 0)
                heat[i] = max(0L, heat[i] - random(0, Cooling));

        // Next drift heat up and diffuse it a little but
        // Macro doesnt work when terhe are multiple instances!!
        // EVERY_N_MILLIS(DriftSpeed)
        // {
        for (int i = 0; i < Size; i++)
            heat[i] = (heat[i] * BlendSelf +
                       heat[(i + 1) % Size] * BlendNeighbor1 +
                       heat[(i + 2) % Size] * BlendNeighbor2 +
                       heat[(i + 3) % Size] * BlendNeighbor3 +
                       heat[(i + 4) % Size] * BlendNeighbor4) /
                      BlendTotal;

        for (int i = 0; i < Sparks; i++)
        {
            if (random(255) < Sparking)
            {
                int y = Size - 1 - random(SparkHeight);
                heat[y] = heat[y] + random(160, 255); // This randomly rolls over sometimes of course, and that's essential to the effect
            }
        }

        // Finally convert heat to a color
        for (int i = 0; i < Size; i++)
        {
            CHSV color = HeatColorHSV(heat[i]);
            int j = bReversed ? (Size - 1 - i) : i;
            drawPrecise(Start + j, 1, color, vleds);
            if (bMirrored)
            {
                int j2 = !bReversed ? (2 * Size - 1 - i) : Size + i;
                drawPrecise(Start + j2, 1, color, vleds);
            }
        }
        // }
    }
};

#endif // FIRE_H