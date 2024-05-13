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

// Naming convention: effectName + "_" + version

std::map<std::string, BaseEffect *> initEffects()
{
    std::map<std::string, BaseEffect *> effects;

    // Blast
    effects["blast_1"] = new Blast();
    effects["blast_america"] = new Blast(america_cp);
    effects["blast_christmas"] = new Blast(christmas_cp);
    effects["blast_mecha"] = new Blast(mecha_cp);
    effects["blast_ice"] = new Blast(ice_cp);
    effects["blast_fire"] = new Blast(fire_cp);

    // Pew
    effects["pew_1"] = new Pew();
    effects["pew_fire"] = new Pew(fire_cp);
    effects["pew_purple"] = new Pew(purple_cp);
    effects["pew_ice"] = new Pew(ice_cp);

    // FireworkShow
    effects["fireworkShow_1"] = new FireworkShow();
    effects["fireworkShow_2"] = new FireworkShow(0.1f, 50.0f);
    effects["big_firework"] = new BigFirework();

    // Flash
    effects["flash_1"] = new Flash();
    effects["panelFlash_2"] = new PanelFlash();
    effects["ringFlash"] = new PanelFlash(rainbow_cp, 16);

    // Twinkle
    effects["twinkle_1"] = new Twinkle();

    // Casimir
    effects["casimir_rainbow"] = new Casimir();
    effects["casimir_1"] = new Casimir(greenDragon_cp);
    effects["casimir_mecha"] = new Casimir(mecha_cp);

    // Lightning
    effects["lightning_1"] = new Lightning(rainbow_cp);

    return effects;
}