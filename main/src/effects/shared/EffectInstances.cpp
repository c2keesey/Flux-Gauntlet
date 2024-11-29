#include "EffectInstances.h"
#include "../gauntlet/g_effects/Pew.h"
#include "../gauntlet/g_effects/Flash.h"
#include "../gauntlet/g_effects/Blast.h"
#include "../shared/effects/FireworkShow.h"
#include "../gauntlet/g_effects/BigFirework.h"
#include "../shared/effects/Twinkle.h"
#include "../gauntlet/g_effects/Casimir.h"
#include "../gauntlet/g_effects/PanelFlash.h"
#include "../gauntlet/g_effects/Lightning.h"
#include "../gauntlet/g_effects/BitSwitch.h"
#include "../gauntlet/g_effects/BlastCollide.h"
#include "../gauntlet/g_effects/ReverseTred.h"
#include "../gauntlet/g_effects/g_Fire.h"
#include "ColorPaletteInstances.h"

// Naming convention: effectName + "_" + version
std::map<std::string, BaseEffect *> initEffects()
{
    std::map<std::string, BaseEffect *> effects;

    // Blast
    effects["blast_1"] = new Blast();
    effects["blast_america"] = new Blast(&america_cp);
    effects["blast_christmas"] = new Blast(&christmas_cp);
    effects["blast_mecha"] = new Blast(&mecha_cp);
    effects["blastCollide_1"] = new BlastCollide();
    effects["blast_simulation"] = new Blast(&simulation_cp);
    effects["blast_pink"] = new Blast(&pink_cp);
    effects["blast_cyan"] = new Blast(&cyan_cp);
    effects["blast_fire"] = new Blast(&fire_cp);
    effects["blast_ice"] = new Blast(&ice_cp);
    effects["blast_white"] = new Blast(&white_cp);

    // Pew
    effects["pew_1"] = new Pew();
    effects["pew_fire"] = new Pew(&fire_cp);
    effects["pew_purple"] = new Pew(&purple_cp);
    effects["pew_ice"] = new Pew(&ice_cp);

    // FireworkShow
    effects["fireworkShow_1"] = new FireworkShow();
    effects["fireworkShow_2"] = new FireworkShow(0.1f, 50.0f);
    effects["big_firework"] = new BigFirework();

    // Flash
    effects["flash_1"] = new Flash();

    effects["panelFlash_2"] = new PanelFlash();
    effects["panelFlash_3"] = new PanelFlash(&white_cp, 3);
    effects["panelFlash_rainbow"] = new PanelFlash(&rainbow_cp, 3);

    effects["ringFlash"] = new PanelFlash(&white_cp, 16);

    // Casimir
    effects["casimir_rainbow"] = new Casimir();
    effects["casimir_1"] = new Casimir(&greenDragon_cp);
    effects["casimir_mecha"] = new Casimir(&mecha_cp);
    effects["casimir_ice"] = new Casimir(&ice_cp);

    // Lightning
    effects["lightning_1"] = new Lightning(&rainbow_cp);
    effects["lightning_cyan"] = new Lightning(&cyan_cp);
    effects["lightning_simulation"] = new Lightning(&simulation_cp);

    // // Ambient effects // //
    // Twinkle
    effects["twinkle_1"] = new Twinkle();
    effects["twinkle_rainbow"] = new Twinkle(20, &rainbow_cp, true, 10);
    effects["twinkle_rainbow_background"] = new Twinkle(20, &rainbow_cp, true, 200);

    // BitSwitch
    effects["bitSwitch_carnival"] = new BitSwitch(&rainbow_cp, true);
    effects["bitSwitch_1"] = new BitSwitch(&ice_cp, true);
    effects["bitSwitch_smooth"] = new BitSwitch(&rainbow_cp, false);

    // ReverseTred
    effects["reverseTred_1"] = new ReverseTred();
    effects["reverseTred_smallfast"] = new ReverseTred(&rainbow_cp, 0.1f, 5, 2);
    effects["reverseTred_longslow"] = new ReverseTred(&rainbow_cp, 0.01f, 20, 10);
    effects["reverseTred_smallfast_vr"] = new ReverseTred(&simulation_cp, 0.1f, 5, 2);

    // Fire
    effects["fire_1"] = new Fire(0, NUM_LEDS, 2, 20, 5, 5, 20, true, false);
    effects["fire_mirrored"] = new Fire(0, NUM_LEDS, 2, 20, 5, 5, 20);

    return effects;
}