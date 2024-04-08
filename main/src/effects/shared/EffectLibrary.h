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
    enum class EffectInst
    {
        BLAST,
        FIREWORK_SHOW,
        RAINBOW_WORM,
        TWINKLE,
        FLASH,
        PEW
    };

    struct PresetContainer
    {
        EffectInst primary;
        EffectInst secondary;
        EffectInst spec;
    };

    EffectLibrary();
    ~EffectLibrary();

    BaseEffect *getEffect(EffectButton button, int index);
    CRGBPalette256 getPalette(int index);
    BaseEffect *getPreset(EffectButton button, Preset preset);
    int getNumEffects(EffectButton button);

private:
    // Effects
    BaseEffect *createEffect(EffectInst effectType);
    static std::vector<EffectInst> primaryEffects;
    static std::vector<EffectInst> secondaryEffects;
    static std::vector<EffectInst> specEffects;
    static std::map<EffectButton, std::vector<EffectInst>> buttonEffectMap;
    static std::map<EffectInst, std::function<BaseEffect *()>> effectFactories;

    // Presets
    static std::map<Preset, PresetContainer> presetMap;
    static PresetContainer action;

    // Palettes
    std::vector<CRGBPalette256> palettes;
};

#endif // EFFECTLIBRARY_H
