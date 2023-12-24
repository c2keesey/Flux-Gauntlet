#ifndef EFFECTLIBRARY_H
#define EFFECTLIBRARY_H

#include <FastLED.h>
#include "shared/BaseEffect.h"
#include "config.h"
#include "palettes.h"

class EffectLibrary
{
private:
    BaseEffect *library[4][NUM_EFFECT_BUTTONS] = {};
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
