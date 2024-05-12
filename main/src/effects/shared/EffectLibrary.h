#ifndef EFFECTLIBRARY_H
#define EFFECTLIBRARY_H

#include <FastLED.h>
#include "effects/BaseEffect.h"
#include "../gauntlet/g_effects/Pew.h"
#include "../gauntlet/g_effects/Flash.h"
#include "../gauntlet/g_effects/Blast.h"
#include "palettes.h"
#include "../../config/config.h"
#include "EffectInstances.h"
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
        BaseEffect *thumb;
        BaseEffect *index;
        BaseEffect *middle;
        BaseEffect *ringf;
        BaseEffect *pinky;
    };

    EffectLibrary();
    ~EffectLibrary();

    void init();

    BaseEffect *getEffect(ButtonEnum button, int index);
    BaseEffect *getPreset(ButtonEnum button, Preset preset) const;
    BaseEffect *getPresetFromI(ButtonEnum button, int index) const;

    int getNumEffects(ButtonEnum button);
    int getNumPresets();

    ColorPalette getPalette(int index);

private:
    // Effects
    std::map<ButtonEnum, std::vector<BaseEffect *>> buttonEffectMap;

    // Presets
    std::map<Preset, PresetContainer> presetMap;

    // Palettes
    std::vector<ColorPalette> palettes;
};

#endif // EFFECTLIBRARY_H