#ifndef EFFECTLIBRARY_H
#define EFFECTLIBRARY_H

#include <FastLED.h>

#include "effects/BaseEffect.h"
#include "effects/Pew.h"
#include "effects/Flash.h"
#include "effects/Blast.h"
#include "effects/RainbowWorm.h"
#include "effects/Twinkle.h"

#include "config.h"
#include "palettes.h"

class EffectLibrary
{
private:
    BaseEffect *library[NUM_PRESETS][NUM_EFFECT_BUTTONS] = {};
    CRGBPalette256 paletteLibrary[5] = {}; // TODO: make this a vector

public:
    EffectLibrary()
    {
        setupEffectsLibrary();
        setupPaletteLibrary();
    }

    ~EffectLibrary()
    {
        for (int i = 0; i < NUM_PRESETS; i++)
        {
            for (int j = 0; j < NUM_EFFECT_BUTTONS; j++)
            {
                delete library[i][j];
            }
        }
    }

    void setupPaletteLibrary()
    {
        paletteLibrary[0] = RainbowColors_p;
        paletteLibrary[1] = ocean_gp_v2;
        paletteLibrary[2] = strong_watermellon;
        paletteLibrary[3] = emerald_dragon;
        paletteLibrary[4] = valentine;
    }

    void setupEffectsLibrary()
    {
        // Action
        library[ACTION_PRESET][PRIMARY_BUTTON] = new Blast();
        library[ACTION_PRESET][SECONDARY_BUTTON] = new Pew();
        library[ACTION_PRESET][SPEC_BUTTON] = new Flash();

        // Ambient
        library[AMBIENT_PRESET][PRIMARY_BUTTON] = new Blast();
        library[AMBIENT_PRESET][SECONDARY_BUTTON] = new Twinkle();
        library[AMBIENT_PRESET][SPEC_BUTTON] = new RainbowWorm();

        // Chill
        library[2][0] = new Blast(ocean_gp_v2);
        library[2][1] = new Twinkle(200, emerald_dragon);
        library[2][2] = new Flash();
    }

    BaseEffect *getEffect(int preset, int button)
    {
        return library[preset][button];
    }

    CRGBPalette256 getPalette(int palette)
    {
        return paletteLibrary[palette];
    }
};

#endif // EFFECTLIBRARY_H