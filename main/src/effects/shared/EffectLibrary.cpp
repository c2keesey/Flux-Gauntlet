
#include <FastLED.h>
#include "EffectLibrary.h"
#include "effects/BaseEffect.h"
#include "../gauntlet/g_effects/Pew.h"
#include "../gauntlet/g_effects/Flash.h"
#include "../gauntlet/g_effects/Blast.h"
#include "effects/RainbowWorm.h"
#include "effects/Twinkle.h"

#include "../../config/config.h"
#include "palettes.h"

EffectLibrary::EffectLibrary()
{
    setupEffectsLibrary();
    setupPaletteLibrary();
}

EffectLibrary::~EffectLibrary()
{
    for (int i = 0; i < NUM_PRESETS; i++)
    {
        for (int j = 0; j < NUM_EFFECT_BUTTONS; j++)
        {
            delete library[i][j];
        }
    }
}

void EffectLibrary::setupPaletteLibrary()
{
    paletteLibrary[0] = RainbowColors_p;
    paletteLibrary[1] = ocean_gp_v2;
    paletteLibrary[2] = strong_watermellon;
    paletteLibrary[3] = emerald_dragon_gp;
    paletteLibrary[4] = valentine;
}

void EffectLibrary::setupEffectsLibrary()
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
    library[2][1] = new Twinkle(200, emerald_dragon_gp);
    library[2][2] = new Flash();

    // Test House
    library[3][0] = new Pew();
    library[3][0]->setSpeed(100);
    library[3][1] = new Twinkle(200, emerald_dragon_gp);
    library[3][2] = new RainbowWorm(emerald_dragon_gp);
}

BaseEffect *EffectLibrary::getEffect(int preset, int button)
{
    return library[preset][button];
}

CRGBPalette256 EffectLibrary::getPalette(int palette)
{
    return paletteLibrary[palette];
}
