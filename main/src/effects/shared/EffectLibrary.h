#ifndef EFFECTLIBRARY_H
#define EFFECTLIBRARY_H

#include <FastLED.h>
#include "effects/BaseEffect.h"
#include "../gauntlet/g_effects/Pew.h"
#include "../gauntlet/g_effects/Flash.h"
#include "../gauntlet/g_effects/Blast.h"
#include "palettes.h"
#include "../../config/config.h"
#include <vector>
#include <map>

class EffectLibrary
{
public:
    // enum class EffectInst
    // {
    //     BLAST,
    //     FIREWORK_SHOW,
    //     RAINBOW_WORM,
    //     TWINKLE,
    //     FLASH,
    //     PEW
    // };

    struct PresetContainer
    {
        BaseEffect *primary;
        BaseEffect *secondary;
        BaseEffect *spec;
    };

    EffectLibrary();
    ~EffectLibrary();

    void init();

    BaseEffect *getEffect(EffectButton button, int index);
    BaseEffect *getPreset(EffectButton button, Preset preset) const;
    BaseEffect *getPresetFromI(EffectButton button, int index) const;

    int getNumEffects(EffectButton button);
    int getNumPresets();

    CRGBPalette256 getPalette(int index);

private:
    // Effects
    std::map<EffectButton, std::vector<BaseEffect *>> buttonEffectMap;

    // Presets
    std::map<Preset, PresetContainer> presetMap;

    // Palettes
    std::vector<CRGBPalette256> palettes;
};

#endif // EFFECTLIBRARY_H