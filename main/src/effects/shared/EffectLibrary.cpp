/**
 * @file EffectLibrary.cpp
 * @brief Implementation of EffectLibrary methods.
 */

#include <FastLED.h>
#include "EffectLibrary.h"
#include "effects/BaseEffect.h"
#include "../gauntlet/g_effects/Pew.h"
#include "../gauntlet/g_effects/Flash.h"
#include "../gauntlet/g_effects/Blast.h"
#include "effects/RainbowWorm.h"
#include "effects/Twinkle.h"
#include "effects/FireworkShow.h"

#include "../../config/config.h"
#include "palettes.h"

EffectLibrary::EffectLibrary()
{
    setupPresets();
    setupEffectLibrary();
    setupPaletteLibrary();
}

EffectLibrary::~EffectLibrary()
{
}

void EffectLibrary::setupPresets()
{
    presetMap[Preset::ACTION] = action;
    presetMap[Preset::TEST] = {EffectInst::FLASH, EffectInst::BLAST, EffectInst::PEW};
}

BaseEffect *EffectLibrary::getPreset(EffectButton button, Preset preset)
{
    PresetContainer p = presetMap[preset];
    EffectInst effect = p.primary;
    if (button == PRIMARY_BUTTON)
    {
        effect = p.primary;
    }
    else if (button == SECONDARY_BUTTON)
    {
        effect = p.secondary;
    }
    else if (button == SPEC_BUTTON)
    {
        effect = p.spec;
    }
    return createEffect(effect);
}

BaseEffect *EffectLibrary::createEffect(EffectInst effectType)
{
    auto it = effectFactories.find(effectType);
    if (it != effectFactories.end())
    {
        return it->second();
    }
    return nullptr;
}

void EffectLibrary::setupPaletteLibrary()
{
    palettes.push_back(RainbowColors_p);
    palettes.push_back(ocean_gp_v2);
    palettes.push_back(strong_watermellon);
    palettes.push_back(emerald_dragon_gp);
    palettes.push_back(valentine);
}

void EffectLibrary::setupEffectLibrary()
{
    for (int i = 0; i < sizeof(primaryEffects) / sizeof(primaryEffects[0]); i++)
    {
        primaryEffects.push_back(primaryEffects[i]);
    }
    for (int i = 0; i < sizeof(secondaryEffects) / sizeof(secondaryEffects[0]); i++)
    {
        secondaryEffects.push_back(secondaryEffects[i]);
    }
    for (int i = 0; i < sizeof(specEffects) / sizeof(specEffects[0]); i++)
    {
        specEffects.push_back(specEffects[i]);
    }
}

// void EffectLibrary::setupEffectLibrary()
// {
//     // Action
//     library[ACTION_PRESET][PRIMARY_BUTTON] = new Blast();
//     Pew *p = new Pew();
//     p->setSpeed(100);
//     library[ACTION_PRESET][SECONDARY_BUTTON] = p;
//     library[ACTION_PRESET][SPEC_BUTTON] = new Flash();

//     // Ambient
//     library[AMBIENT_PRESET][PRIMARY_BUTTON] = new Blast();
//     library[AMBIENT_PRESET][SECONDARY_BUTTON] = new Twinkle();
//     library[AMBIENT_PRESET][SPEC_BUTTON] = new RainbowWorm();

//     // Chill
//     library[2][0] = new Blast(ocean_gp_v2);
//     library[2][1] = new Twinkle(200, emerald_dragon_gp);
//     library[2][2] = new Flash();

//     // Fireworks
//     library[3][0] = new Blast();
//     library[3][1] = new FireworkShow(10, DEFAULT_PALETTE, 0.03f, 50.0f);
//     library[3][2] = new RainbowWorm(emerald_dragon_gp);

// Broken Spec
// library[0][PRIMARY_BUTTON] = new Blast();
// library[0][SECONDARY_BUTTON] = new FireworkShow(10, DEFAULT_PALETTE, 0.03f, 50.0f);

// library[1][PRIMARY_BUTTON] = new Blast();
// library[1][SECONDARY_BUTTON] = new RainbowWorm(emerald_dragon_gp);

// library[2][PRIMARY_BUTTON] = new Blast();
// Pew *p = new Pew();
// p->setSpeed(75);
// library[2][SECONDARY_BUTTON] = p;

// library[3][PRIMARY_BUTTON] = new Blast(emerald_dragon_gp);
// library[3][SECONDARY_BUTTON] = new Twinkle(200, emerald_dragon_gp);

// library[4][PRIMARY_BUTTON] = new Blast(emerald_dragon_gp);
// Pew *p2 = new Pew(purple_gp);
// p2->setSpeed(75);
// library[4][SECONDARY_BUTTON] = p2;

// library[5][PRIMARY_BUTTON] = new Blast(blue_gp);
// library[5][SECONDARY_BUTTON] = new Blast(red_gp);
// }

// TODO: Check index bounds
BaseEffect *EffectLibrary::getEffect(EffectButton button, int index)
{
    if (button == PRIMARY_BUTTON)
    {
        return createEffect(primaryEffects[index]);
    }
    else if (button == SECONDARY_BUTTON)
    {
        return createEffect(secondaryEffects[index]);
    }
    else if (button == SPEC_BUTTON)
    {
        return createEffect(specEffects[index]);
    }
    return nullptr;
}

CRGBPalette256 EffectLibrary::getPalette(int index)
{
    return palettes[index];
}

int EffectLibrary::getNumEffects(EffectButton button)
{
    return buttonEffectMap[button].size();
}