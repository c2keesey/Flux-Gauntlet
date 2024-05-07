#ifndef PANELFLASH_H
#define PANELFLASH_H

#include "../../shared/effects/BaseEffect.h"
#include "../../shared/EffectHelpers.h"
#include <vector>

class PanelFlash : public BaseEffect
{
private:
    int numPanels;
    int panelIndex = 0;
    int *breakPoints;

public:
    PanelFlash(CRGBPalette256 pal = DEFAULT_PALETTE, int numPanels = 2) : BaseEffect(pal)
    {
        if (numPanels < 1)
        {
            numPanels = 1;
        }
        this->numPanels = numPanels;
        breakPoints = new int[numPanels + 1];
        for (int i = 0; i < numPanels; i++)
        {
            breakPoints[i] = i * NUM_LEDS / numPanels;
        }
    }

    ~PanelFlash()
    {
        delete[] breakPoints;
    }

    void trigger() override
    {
        for (int i = breakPoints[panelIndex]; i < breakPoints[panelIndex + 1]; i++)
        {
            vleds[i] = CHSV(0, 0, 255);
        }
    }

    void update() override
    {
        for (int i = 0; i < NUM_LEDS; i++)
        {
            vleds[i] = CHSV(0, 0, 0); // TODO: make
        }
    }
};

#endif // PANELFLASH_H