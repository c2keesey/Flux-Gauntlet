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
    int lastPanel = 0;
    Rings rings;

public:
    PanelFlash(CRGBPalette256 pal = DEFAULT_PALETTE, int numPanels = 2) : BaseEffect(pal), rings(vleds)
    {
        minUpdatePeriod = 100;
        if (numPanels < 1)
        {
            numPanels = 1;
        }
        this->numPanels = numPanels;
        int numRings = rings.getNumRings();
        breakPoints = new int[numPanels + 1];
        for (int i = 0; i <= numPanels; i++)
        {
            breakPoints[i] = rings.getRingStart(i * numRings / numPanels);
        }
    }

    ~PanelFlash()
    {
        delete[] breakPoints;
    }

    void trigger() override
    {
        int newPanelIndex;
        do
        {
            newPanelIndex = random(0, numPanels);
        } while (newPanelIndex == panelIndex);

        panelIndex = newPanelIndex;

        for (int i = breakPoints[panelIndex]; i < breakPoints[panelIndex + 1]; i++)
        {
            vleds[i] = CHSV(0, 0, 255);
        }
    }

    void update() override
    {
        for (int i = 0; i < NUM_LEDS; i++)
        {
            vleds[i].v = qsub8(vleds[i].v, 10);
        }
    }
};

#endif // PANELFLASH_H