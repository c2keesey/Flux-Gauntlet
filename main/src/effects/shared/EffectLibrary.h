#ifndef EFFECTLIBRARY_H
#define EFFECTLIBRARY_H

#include <FastLED.h>
#include "effects/BaseEffect.h"
#include "palettes.h"
#include "../../config/config.h"

class EffectLibrary
{
private:
    BaseEffect *library[NUM_PRESETS][NUM_EFFECT_BUTTONS] = {};
    CRGBPalette256 paletteLibrary[5] = {}; // TODO: make this a vector

public:
    EffectLibrary();
    ~EffectLibrary();

    void setupPaletteLibrary();
    void setupEffectsLibrary();

    BaseEffect *getEffect(int preset, int button);
    CRGBPalette256 getPalette(int palette);
};

#endif // EFFECTLIBRARY_H
